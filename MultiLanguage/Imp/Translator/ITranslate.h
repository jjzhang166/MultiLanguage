#ifndef __ITRANSLATE_H__
#define __ITRANSLATE_H__

#include <string>
using std::string;

class ITranslate
{
public:
    virtual string translate(const string &origin_text, const string &domain) const = 0;
    virtual string reverse_translate(const string &trans_text, const string &domain) const = 0;

    virtual void setDebug(bool bIsEnable) = 0;

protected:
    ~ITranslate() {}
};

#endif //__ITRANSLATE_H__
