#include "TwoLevelMapTranslator.h"
#include <boost/foreach.hpp>
#include <boost/typeof/typeof.hpp>

void TwoLevelMapTranslator::insertItemInDict(PrefixDict &dict, const string &prefix, const string &key, const string &value)
{
    BOOST_AUTO(iter, dict.find(prefix));
    if (iter == dict.end()) {
        ItemDict item_dict;
        item_dict.insert(std::make_pair(key, value));
        dict.insert(std::make_pair(prefix, item_dict));
    } else {
        ItemDict &item_dict = iter->second;
        item_dict.insert(std::make_pair(key, value));
    }
}

void TwoLevelMapTranslator::importItems(const list<TransItem> &items)
{
    BOOST_FOREACH(const TransItem &item, items) {
        insertItemInDict(m_dict, item.prefix, item.origin_text, item.trans_text);
        insertItemInDict(m_reverse_dict, item.prefix, item.trans_text, item.origin_text);
    }
}

void TwoLevelMapTranslator::exportItems(list<TransItem> &items) const
{
    BOOST_AUTO(prefix_c_iter, m_dict.begin());
    while (prefix_c_iter != m_dict.end()) {
        string prefix = prefix_c_iter->first;
        const ItemDict &itemDict = prefix_c_iter->second;
        BOOST_AUTO(item_c_iter, itemDict.begin());
        while (item_c_iter != itemDict.end()) {
            string origin = item_c_iter->first;
            string trans = item_c_iter->second;
            items.push_back(TransItem(origin, trans, prefix));
            ++ item_c_iter;
        }
        ++ prefix_c_iter;
    }
}

string TwoLevelMapTranslator::findItemInDict(const PrefixDict &dict, const string &prefix, const string &text) const
{
    PrefixDict::const_iterator c_prefix_iter = dict.find(prefix);
    if (c_prefix_iter != dict.end()) {
        const ItemDict &itemDict = c_prefix_iter->second;
        ItemDict::const_iterator c_item_iter = itemDict.find(text);
        if (c_item_iter != itemDict.end()) {
            return c_item_iter->second;
        }
    }
    return text;
}

string TwoLevelMapTranslator::translate(const string &origin_text, const string &prefix) const
{
    return findItemInDict(m_dict, prefix, origin_text);
}

string TwoLevelMapTranslator::reverse_translate(const string &trans_text, const string &prefix) const
{
    return findItemInDict(m_reverse_dict, prefix, trans_text);
}
