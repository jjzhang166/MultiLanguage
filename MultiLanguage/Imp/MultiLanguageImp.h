#ifndef __MULTI_LANGUAGE_IMP_H__
#define __MULTI_LANGUAGE_IMP_H__

#include <string>
#include <boost/shared_ptr.hpp>

using std::string;
using boost::shared_ptr;

class Translator;
class Loader;

class MultiLanguageImp
{
public:
    MultiLanguageImp();

public:
    enum FileType { XML, TXT };
    void setFileType(FileType type);

    bool setFilePath(const string &path);
    bool setLanguage(const string &language);

    void setDebug(bool bIsEnable);

    string translate(const string &origin_text, const string &domain) const;
    string reverse_translate(const string &trans_text, const string &domain) const;

    void reload();

protected:
    shared_ptr<Loader> makeLoader();

private:
    shared_ptr<Translator> m_sptrTranslator;
    string m_strPath;
    FileType m_eFileType;
    string m_strCurrLanguage;
};

#endif //__MULTI_LANGUAGE_IMP_H__
