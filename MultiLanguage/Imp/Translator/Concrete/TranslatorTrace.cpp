
#include "TranslatorTrace.h"
#include <fstream>
#include <iostream>
#include <boost/typeof/typeof.hpp>
#include <boost/foreach.hpp>

TranslatorTrace::TranslatorTrace(shared_ptr<Translator> sptrTranslator)
    : m_sptrTranslator(sptrTranslator)
{
    //! Must enable m_sptrTranslator 's Debug mode.
    m_sptrTranslator->setDebug(true);
}

TranslatorTrace::~TranslatorTrace()
{
    try {
        exportMissItemsTo("miss_trans_items.txt");
    } catch (...) {

    }
}

void TranslatorTrace::clearItems()
{
    m_sptrTranslator->clearItems();
}

void TranslatorTrace::importItems(const list<TransItem> &trans_items,
                             const list<DomainInhertUnit> &domain_inhert_list)
{
    m_sptrTranslator->importItems(trans_items, domain_inhert_list);
}

void TranslatorTrace::exportItems(list<TransItem> &items) const
{
    m_sptrTranslator->exportItems(items);
}

string TranslatorTrace::translate(const string &origin_text, const string &domain) const
{
    string trans_text = m_sptrTranslator->translate(origin_text, domain);
    if (origin_text.size() > 0 && trans_text.at(0) == '!') {
        const_cast<TranslatorTrace*>(this)->appendToMissTransItem(origin_text, domain);
    }
    return trans_text;
}

string TranslatorTrace::reverse_translate(const string &trans_text, const string &domain) const
{
    return m_sptrTranslator->reverse_translate(trans_text, domain);
}

void TranslatorTrace::setDebug(bool)
{
    //! Needn't do anything
}

void TranslatorTrace::appendToMissTransItem(const string &origin_text, const string &domain)
{
    BOOST_AUTO(domain_iter, m_mapDomains.find(domain));
    if (domain_iter != m_mapDomains.end()) {
        ItemSet &item_dict = domain_iter->second;
        BOOST_AUTO(item_iter, item_dict.find(origin_text));
        if (item_iter == item_dict.end()) {
            item_dict.insert(origin_text);
        }
    } else {
        ItemSet newSet;
        newSet.insert(origin_text);
        m_mapDomains.insert(std::make_pair(domain, newSet));
    }
}

/**
 * \brief Save miss items into file
 */
void TranslatorTrace::exportMissItemsTo(const string &filename)
{
    using namespace std;

    ofstream file;
    file.open(filename.c_str(), ios_base::app | ios_base::out);
    if (!file) {
        cerr << "ERROR: Open " << filename << " fail!" << endl;
        return;
    }

    typedef pair<const string, ItemSet> DomainItem;
    BOOST_FOREACH(DomainItem &domain_item, m_mapDomains) {
        const string &domain_name = domain_item.first;
        const ItemSet &item_set = domain_item.second;
        file << "[" << domain_name << "]" << endl;
        BOOST_FOREACH(const string &trans_item, item_set) {
            file << trans_item << '=' << endl;
        }
        file << endl;
    }

    file.close();
}
