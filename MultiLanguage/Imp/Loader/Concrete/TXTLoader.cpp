#include "TXTLoader.h"
#include <fstream>

using namespace std;

bool TXTLoader::isPrefix(const string str) const
{
    //!TODO
    (void)str;
    return false;
}

bool TXTLoader::parseAsPrefix(const string &str) const
{
    //!TODO
    (void)str;
    return false;
}

bool TXTLoader::parseAsKeyValue(const string &str) const
{
    //!TODO
    (void)str;
    return false;
}

bool TXTLoader::parseOneLine(const string &str) const
{
    //!TODO
    (void)str;
    return false;
}

bool TXTLoader::parseFile(const string &fileName) const
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
    return true;
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
