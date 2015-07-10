#ifndef __LOADER_H__
#define __LOADER_H__

#include <string>
#include <boost/weak_ptr.hpp>

using std::string;
using boost::weak_ptr;

class IImportAndExport;

class Loader
{
public:
    virtual ~Loader() {}

public:
    void setTranslator(weak_ptr<IImportAndExport> wptrTranslator);

    virtual bool loadFrom(const string &fileName) = 0;

protected:
    weak_ptr<IImportAndExport> m_wptrTranslator;
};

#endif //__LOADER_H__
