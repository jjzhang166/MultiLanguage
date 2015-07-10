#ifndef __IIMPORT_AND_EXPORT_H__
#define __IIMPORT_AND_EXPORT_H__

#include <string>
#include <list>
using std::string;
using std::list;

struct TransItem
{
    TransItem(const string &o, const string &t, const string &p)
        : origin_text(o), trans_text(t), domain(p) {}

    string origin_text;
    string trans_text;
    string domain;
};

typedef std::pair<string, string> DomainInhertUnit;

class IImportAndExport
{
public:
    virtual void clearItems() = 0;
    virtual void importItems(const list<TransItem> &trans_items,
                             const list<DomainInhertUnit> &domain_inhert_list) = 0;
    virtual void exportItems(list<TransItem> &items) const = 0;

protected:
    ~IImportAndExport() {}
};

#endif //__IIMPORT_AND_EXPORT_H__
