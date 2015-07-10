#include "MultiLanguageImp.h"
#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>

#include "Translator/Translator.h"

#include "Loader/Concrete/XMLLoader.h"
#include "Loader/Concrete/TXTLoader.h"

using boost::make_shared;

MultiLanguageImp::MultiLanguageImp()
    : m_eFileType(TXT)
{
    m_sptrTranslator = Translator::make();
}

bool MultiLanguageImp::setFilePath(const string &path)
{
    using namespace boost;
    filesystem::path p(path);
    if (filesystem::exists(p)) {
        m_strPath = path;
        return true;
    }
    return false;
}

void MultiLanguageImp::setFileType(FileType type)
{
    m_eFileType = type;
}

bool MultiLanguageImp::setLanguage(const string &language)
{
    shared_ptr<Loader> loader = makeLoader();

    loader->setTranslator(m_sptrTranslator);

    string fileName = "language_" + language + "."
                      + (m_eFileType == TXT ? "txt" : "xml");

    string fullFileName = m_strPath + "/" + fileName;

    m_strCurrLanguage = language;

    m_sptrTranslator->clearItems();
    return loader->loadFrom(fullFileName);
}

void MultiLanguageImp::setDebug(bool bIsEnable)
{
    m_sptrTranslator->setDebug(bIsEnable);
}

shared_ptr<Loader> MultiLanguageImp::makeLoader()
{
    if (m_eFileType == XML) {
        return make_shared<XMLLoader>();
    } else if (m_eFileType == TXT) {
        return make_shared<TXTLoader>();
    } else {
        assert(false);
    }
}

string MultiLanguageImp::translate(const string &origin_text, const string &domain) const
{
    return m_sptrTranslator->translate(origin_text, domain);
}

string MultiLanguageImp::reverse_translate(const string &trans_text, const string &domain) const
{
    return m_sptrTranslator->reverse_translate(trans_text, domain);
}

void MultiLanguageImp::reload()
{
    if (!m_strCurrLanguage.empty()) {
        setLanguage(m_strCurrLanguage);
    }
}
