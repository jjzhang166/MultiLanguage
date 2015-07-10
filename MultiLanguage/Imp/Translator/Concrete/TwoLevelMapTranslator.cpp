#include "TwoLevelMapTranslator.h"
#include <boost/foreach.hpp>
#include <boost/typeof/typeof.hpp>

TwoLevelMapTranslator::TwoLevelMapTranslator()
    : m_bIsDebugEnable(false)
{}

void TwoLevelMapTranslator::insertItemInDict(PrefixDict &dict, const string &domain, const string &key, const string &value)
{
    BOOST_AUTO(iter, dict.find(domain));
    if (iter == dict.end()) {
        ItemDict item_dict;
        item_dict.insert(std::make_pair(key, value));
        dict.insert(std::make_pair(domain, item_dict));
    } else {
        ItemDict &item_dict = iter->second;
        item_dict.insert(std::make_pair(key, value));
    }
}

void TwoLevelMapTranslator::clearItems()
{
    m_dict.clear();
    m_reverse_dict.clear();
}

void TwoLevelMapTranslator::importItems(const list<TransItem> &trans_items,
                                        const list<DomainInhertUnit>& domain_inhert_list)
{
    BOOST_FOREACH(const TransItem &item, trans_items) {
        insertItemInDict(m_dict, item.domain, item.origin_text, item.trans_text);
        insertItemInDict(m_reverse_dict, item.domain, item.trans_text, item.origin_text);
    }

    BOOST_FOREACH(const DomainInhertUnit& item, domain_inhert_list) {
        m_domain_dict.insert(item);
    }
}

void TwoLevelMapTranslator::exportItems(list<TransItem> &items) const
{
    BOOST_AUTO(prefix_c_iter, m_dict.begin());
    while (prefix_c_iter != m_dict.end()) {
        string domain = prefix_c_iter->first;
        const ItemDict &itemDict = prefix_c_iter->second;
        BOOST_AUTO(item_c_iter, itemDict.begin());
        while (item_c_iter != itemDict.end()) {
            string origin = item_c_iter->first;
            string trans = item_c_iter->second;
            items.push_back(TransItem(origin, trans, domain));
            ++ item_c_iter;
        }
        ++ prefix_c_iter;
    }
}

string TwoLevelMapTranslator::findItemInDict(const PrefixDict &dict,
                                             const string &domain,
                                             const string &text) const
{
    if (text.empty())
        return text;

    PrefixDict::const_iterator c_prefix_iter = dict.find(domain);
    if (c_prefix_iter != dict.end()) {
        const ItemDict &itemDict = c_prefix_iter->second;
        ItemDict::const_iterator c_item_iter = itemDict.find(text);
        if (c_item_iter != itemDict.end()) {
            string value = c_item_iter->second;
            //! Found it, but it is empty
            if (value.empty()) {
                if (m_bIsDebugEnable)
                    value = string("?") + text + '?';
                else
                    value = text;
            }
            return value;
        }
    }

    //! Find it in base domain
    BOOST_AUTO(base_domain_iter, m_domain_dict.find(domain));
    if (base_domain_iter != m_domain_dict.end()) {
        return findItemInDict(dict, base_domain_iter->second, text);
    }

    //! Cann't Found it
    if (m_bIsDebugEnable) {
        return string("!") + text + '!';
    } else {
        return text;
    }
}

void TwoLevelMapTranslator::setDebug(bool bIsEnable)
{
    m_bIsDebugEnable = bIsEnable;
}

string TwoLevelMapTranslator::translate(const string &origin_text, const string &domain) const
{
    return findItemInDict(m_dict, domain, origin_text);
}

string TwoLevelMapTranslator::reverse_translate(const string &trans_text, const string &domain) const
{
    return findItemInDict(m_reverse_dict, domain, trans_text);
}
