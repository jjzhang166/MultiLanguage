#include "TXTLoader.h"
#include <fstream>
#include <boost/shared_ptr.hpp>
#include "../../Translator/IImportAndExport.h"

using namespace std;

/**
 * \bref    分析一行，判别出它是[xx]还是key=value。返回类型
 * \param   str
 * \return  ELineType
 */
TXTLoader::ELineType TXTLoader::analyseLineType(const string str) const
{
    if (str[0] == '[' && str[str.length()-1] == ']')
        return PREFIX;

    if (str.find('=') != string::npos)
        return ITEM;

    return ERROR;
}

bool TXTLoader::parseAsPrefix(const string &str)
{
    string strPrefix = str.substr(1, str.length()-2);
    strPrefix = stringStrip(strPrefix);
    strPrefix = convertSpecialChar(strPrefix);

    m_strCurrPrefix = strPrefix;
    return true;
}

bool TXTLoader::parseAsKeyValue(const string &str)
{
    string::size_type separatePos = str.find_first_of('=');
    if (separatePos != string::npos) {
        string strKey = str.substr(0, separatePos);
        strKey = stringStrip(strKey);
        strKey = convertSpecialChar(strKey);

        string strValue = str.substr(separatePos+1);
        strValue = stringStrip(strValue);
        strValue = convertSpecialChar(strValue);

        m_lstItems.push_back(TransItem(strKey, strValue, m_strCurrPrefix));
        return true;
    }
    return false;
}

bool TXTLoader::parseOneLine(const string &str)
{
    string strLine = cutComment(str);
    strLine = stringStrip(strLine);

    ELineType type = analyseLineType(strLine);
    if (type == PREFIX) {
        return parseAsPrefix(strLine);
    } else if (type == ITEM) {
        return parseAsKeyValue(strLine);
    } else {
        return false;
    }
    return false;
}

bool TXTLoader::parseFile(const string &fileName)
{
    ifstream ifile;
    ifile.open(fileName.c_str());
    if (!ifile) {
        return false;
    }
    string line;
    while (getline(ifile, line)) {
        parseOneLine(line);
    }
    ifile.close();

    boost::shared_ptr<IImportAndExport> sptr = m_wptrTranslator.lock();
    if (sptr) {
        sptr->importItems(m_lstItems);
        return true;
    }
    return false;
}

bool TXTLoader::loadFrom(const string &fileName)
{
    return parseFile(fileName);
}

bool TXTLoader::saveTo(const string &fileName)
{
    //!TODO
    (void)fileName;
    return false;
}


string TXTLoader::cutComment(const string &str) const
{
    //!TODO:
    return str;
}

string TXTLoader::stringStrip(const string &str) const
{
    //!TODO:
    return str;
}

string TXTLoader::convertSpecialChar(const string &str) const
{
    //!TODO:
    return str;
}
