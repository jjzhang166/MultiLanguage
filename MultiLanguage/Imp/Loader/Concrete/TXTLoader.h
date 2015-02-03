#ifndef __TXT_LOADER_H__
#define __TXT_LOADER_H__

#include "../Loader.h"

class TXTLoader : public Loader
{
public:
    virtual bool loadFrom(const string &fileName);
    virtual bool saveTo(const string &fileName);

protected:
    bool isPrefix(const string str) const;
    bool parseAsPrefix(const string &str) const;
    bool parseAsKeyValue(const string &str) const;
    bool parseOneLine(const string &str) const;
    bool parseFile(const string &fileName) const;

private:
    string m_strCurrPreset;
};

#endif //__TXT_LOADER_H__
