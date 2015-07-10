#ifndef TRANSLATORTRACE_H
#define TRANSLATORTRACE_H

#include <map>
#include <set>
#include "../Translator.h"

using boost::shared_ptr;

//! Using Decoder pattern, TranslatorTrace traces translate operation.
//! Record those item that translate fail, and print those item group
//! by domain

class TranslatorTrace : public Translator
{
public:
    TranslatorTrace(shared_ptr<Translator> sptrTranslator);
    ~TranslatorTrace();

    virtual void clearItems();
    virtual void importItems(const list<TransItem> &trans_items,
                             const list<DomainInhertUnit> &domain_inhert_list);
    virtual void exportItems(list<TransItem> &items) const;

    virtual string translate(const string &origin_text, const string &domain) const;
    virtual string reverse_translate(const string &trans_text, const string &domain) const;

    virtual void setDebug(bool bIsEnable);

protected:
    void appendToMissTransItem(const string &origin_text, const string &domain);
    void exportMissItemsTo(const string &filename);

private:
    shared_ptr<Translator> m_sptrTranslator;

    typedef std::set<string> ItemSet;
    typedef std::map<string, ItemSet> DomainDict;

    DomainDict m_mapDomains;
};

#endif // TRANSLATORTRACE_H
