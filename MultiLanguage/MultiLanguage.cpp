#include "MultiLanguage.h"
#include <boost/make_shared.hpp>
#include "Imp/MultiLanguageImp.h"

MultiLanguage::MultiLanguage()
{
    m_sptrImp = boost::make_shared<MultiLanguageImp>();
    m_sptrImp->setFilePath("");
    m_sptrImp->setFileType("xml");
    m_sptrImp->setLanguage("en");
}

void MultiLanguage::setLanguage(const string &language)
{
    m_sptrImp->setLanguage(language);
}

string MultiLanguage::translate(const string &origin_text, const string &prefix) const
{
    return m_sptrImp->translate(origin_text, prefix);
}

string MultiLanguage::reverse_translate(const string &trans_text, const string &prefix) const
{
    return m_sptrImp->reverse_translate(trans_text, prefix);
}
