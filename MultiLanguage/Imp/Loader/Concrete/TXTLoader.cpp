#include "TXTLoader.h"
#include <fstream>
#include <boost/shared_ptr.hpp>
#include "../../Translator/IImportAndExport.h"
#include "Util.h"

using namespace std;

string strip_and_convert(const string &src)
{
    using namespace Util;
    return convert_special_chars(string_strip(src));
}

TXTLoader::ELineType TXTLoader::analyseLineType(const string str) const
{
    if (str[0] == '[' && str[str.length()-1] == ']')
        return PREFIX;

    if (str.find('=') != string::npos)
        return ITEM;

    return ERROR;
}

bool TXTLoader::parseAsDomain(const string &str)
{
    string strDomain = str.substr(1, str.length()-2);

    string::size_type colon_pos = strDomain.find_first_of(':');
    if (colon_pos != string::npos) {
        string strDerive = strip_and_convert(strDomain.substr(0, colon_pos));
        string strBase   = strip_and_convert(strDomain.substr(colon_pos+1));
        m_lstDomains.push_back(make_pair(strDerive, strBase));
        m_strCurrDomain = strDerive;
    } else {
        m_strCurrDomain = strip_and_convert(strDomain);
    }

    return true;
}

bool TXTLoader::parseAsItem(const string &str)
{
    string::size_type separaterPos = str.find_first_of('=');
    if (separaterPos != string::npos) {
        string strKey   = Util::string_strip(str.substr(0, separaterPos));
        string strValue = Util::string_strip(str.substr(separaterPos+1));

        strKey   = Util::convert_special_chars(strKey);
        strValue = Util::convert_special_chars(strValue);

        m_lstItems.push_back(TransItem(strKey, strValue, m_strCurrDomain));
    }
    return false;
}

bool TXTLoader::parseOneLine(const string &str)
{
    string strWithoutComment = cutComment(str);
    string strStriped = Util::string_strip(strWithoutComment);

    ELineType type = analyseLineType(strStriped);
    if (type == PREFIX) {
        return parseAsDomain(strStriped);
    } else if (type == ITEM) {
        return parseAsItem(strStriped);
    } else {
        return false;
    }
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
        sptr->importItems(m_lstItems, m_lstDomains);
        return true;
    }

    return false;
}

bool TXTLoader::loadFrom(const string &fileName)
{
    return parseFile(fileName);
}

string TXTLoader::cutComment(const string &strOrig) const
{
    string::size_type pos = strOrig.find_first_of('#');
    if (pos != string::npos) {
        return strOrig.substr(0, pos);
    } else {
        return strOrig;
    }
}

