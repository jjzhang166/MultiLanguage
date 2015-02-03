#ifndef __TWO_LEVEL_TRANSLATOR_H__
#define __TWO_LEVEL_TRANSLATOR_H__

#include <map>
#include "../Translator.h"

class TwoLevelMapTranslator : public Translator
{
public:
    virtual void importItems(const list<TransItem> &items);
    virtual void exportItems(list<TransItem> &items) const;

public:
    virtual string translate(const string &origin_text, const string &prefix) const;
    virtual string reverse_translate(const string &trans_text, const string &prefix) const;

private:
    typedef std::map<string, string> ItemDict;
    typedef std::map<string, ItemDict> PrefixDict;

    string findItemInDict(const PrefixDict &dict, const string &prefix, const string &text) const;
    void insertItemInDict(PrefixDict &dict, const string &prefix, const string &key, const string &value);

    PrefixDict m_dict;
    PrefixDict m_reverse_dict;
};

#endif //__TWO_LEVEL_TRANSLATOR_H__
