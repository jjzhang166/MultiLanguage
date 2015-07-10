#ifndef __TXT_LOADER_H__
#define __TXT_LOADER_H__

#include "../Loader.h"
#include "../../Translator/IImportAndExport.h"

using std::string;

class TXTLoader : public Loader
{
public:
    virtual bool loadFrom(const string &fileName);

protected:
    enum ELineType { ERROR, PREFIX, ITEM };
    ELineType analyseLineType(const string str) const;

    bool parseAsDomain(const string &str);
    bool parseAsItem(const string &str);
    bool parseOneLine(const string &str);
    bool parseFile(const string &fileName);

    string cutComment(const string &str) const;

private:
    string m_strCurrDomain;
    list<TransItem> m_lstItems;
    list<DomainInhertUnit> m_lstDomains;
};

#endif //__TXT_LOADER_H__
