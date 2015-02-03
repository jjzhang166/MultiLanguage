#ifndef __MULTI_LANGUAGE_H__
#define __MULTI_LANGUAGE_H__

#include <string>
#include <boost/shared_ptr.hpp>

using std::string;
using boost::shared_ptr;

class MultiLanguageImp;

class MultiLanguage
{
public:
    MultiLanguage();

public:
    void setLanguage(const string &language);

    string translate(const string &origin_text, const string &prefix) const;
    string reverse_translate(const string &trans_text, const string &prefix) const;

private:
    shared_ptr<MultiLanguageImp> m_sptrImp;
};

#endif //__MULTI_LANGUAGE_H__
