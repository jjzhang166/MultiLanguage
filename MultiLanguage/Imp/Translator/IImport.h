#ifndef __IIMPORT_H__
#define __IIMPORT_H__

#include <string>
#include <list>
using std::string;
using std::list;

struct TransItem
{
    TransItem(const string &o, const string &t, const string &p)
        : origin_text(o), trans_text(t), prefix(p) {}

    string origin_text;
    string trans_text;
    string prefix;
};

class IImport
{
public:
    virtual void clearItems() = 0;
    virtual void importItems(const list<TransItem> &items) = 0;
    virtual void exportItems(list<TransItem> &items) const = 0;

protected:
    ~IImport() {}
};

#endif //__IIMPORT_H__
