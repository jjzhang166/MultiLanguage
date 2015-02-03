#include "MultiLanguageImp.h"
#include <boost/make_shared.hpp>

#include "Translator/Concrete/TwoLevelMapTranslator.h"

#include "Loader/Concrete/XMLLoader.h"
#include "Loader/Concrete/TXTLoader.h"

using boost::make_shared;

MultiLanguageImp::MultiLanguageImp()
{
    m_sptrTranslator = make_shared<TwoLevelMapTranslator>();
}

void MultiLanguageImp::setFilePath(const string &path)
{
    //!TODO: Check the path
    m_strPath = path;
}

void MultiLanguageImp::setFileType(const string &type)
{
    m_strPath = type;
}

bool MultiLanguageImp::setLanguage(const string &language)
{
    shared_ptr<Loader> loader = makeLoader();

    loader->setTranslator(m_sptrTranslator);

    string fileName = "language_" + language + "." + m_strFileType;
    string fullFileName = m_strPath + "/" + fileName;

    return loader->loadFrom(fullFileName);
}

shared_ptr<Loader> MultiLanguageImp::makeLoader()
{
    if (m_strFileType == "xml") {
        return make_shared<XMLLoader>();
    } else if (m_strFileType == "txt") {
        return make_shared<TXTLoader>();
    } else {
        assert(false);
    }
}

string MultiLanguageImp::translate(const string &origin_text, const string &prefix) const
{
    return m_sptrTranslator->translate(origin_text, prefix);
}

string MultiLanguageImp::reverse_translate(const string &trans_text, const string &prefix) const
{
    return m_sptrTranslator->reverse_translate(trans_text, prefix);
}
