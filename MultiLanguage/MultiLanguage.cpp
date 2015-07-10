#include "MultiLanguage.h"
#include <boost/make_shared.hpp>
#include "Imp/MultiLanguageImp.h"

MultiLanguage::MultiLanguage()
{
    m_sptrImp = boost::make_shared<MultiLanguageImp>();
    m_sptrImp->setFilePath("");
    m_sptrImp->setLanguage("en");
}

bool MultiLanguage::setFilePath(const string &path)
{
    return m_sptrImp->setFilePath(path);
}

bool MultiLanguage::setLanguage(const string &language)
{
    return m_sptrImp->setLanguage(language);
}

void MultiLanguage::setDebug(bool bIsEnable)
{
    m_sptrImp->setDebug(bIsEnable);
}

string MultiLanguage::translate(const string &origin_text, const string &domain) const
{
    return m_sptrImp->translate(origin_text, domain);
}

string MultiLanguage::reverse_translate(const string &trans_text, const string &domain) const
{
    return m_sptrImp->reverse_translate(trans_text, domain);
}

void MultiLanguage::reload()
{
    return m_sptrImp->reload();
}
