#ifndef __TWO_LEVEL_TRANSLATOR_H__
#define __TWO_LEVEL_TRANSLATOR_H__

#include <map>
#include "../Translator.h"

class TwoLevelMapTranslator : public Translator
{
public:
    TwoLevelMapTranslator();

    virtual void clearItems();
    virtual void importItems(const list<TransItem> &trans_items,
                             const list<DomainInhertUnit> &domain_inhert_list);
    virtual void exportItems(list<TransItem> &items) const;

public:
    virtual string translate(const string &origin_text, const string &domain) const;
    virtual string reverse_translate(const string &trans_text, const string &domain) const;
    virtual void setDebug(bool bIsEnable);

private:
    typedef std::map<string, string> ItemDict;
    typedef std::map<string, ItemDict> PrefixDict;
    typedef std::map<string, string> DomainDict;

    string findItemInDict(const PrefixDict &dict, const string &domain, const string &text) const;
    void insertItemInDict(PrefixDict &dict, const string &domain, const string &key, const string &value);

private:
    bool m_bIsDebugEnable;
    DomainDict m_domain_dict;
    PrefixDict m_dict;
    PrefixDict m_reverse_dict;
};

#endif //__TWO_LEVEL_TRANSLATOR_H__
