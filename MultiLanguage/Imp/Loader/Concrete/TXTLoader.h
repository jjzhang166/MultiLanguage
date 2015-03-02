#ifndef __TXT_LOADER_H__
#define __TXT_LOADER_H__

#include <list>
#include "../Loader.h"
#include "../../Translator/IImport.h"

using std::list;

class TXTLoader : public Loader
{
public:
    virtual bool loadFrom(const string &fileName);
    virtual bool saveTo(const string &fileName);

protected:
    enum ELineType { ERROR, PREFIX, ITEM };
    ELineType analyseLineType(const string str) const;

    bool parseAsPrefix(const string &str);
    bool parseAsKeyValue(const string &str);
    bool parseOneLine(const string &str);
    bool parseFile(const string &fileName);

    string cutComment(const string &str) const;
    string stringStrip(const string &str) const;
    string convertSpecialChar(const string &str) const;

private:
    string m_strCurrPrefix;
    list<TransItem> m_lstItems;
};

#endif //__TXT_LOADER_H__
