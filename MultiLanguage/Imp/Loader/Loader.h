#ifndef __LOADER_H__
#define __LOADER_H__

#include <string>
#include <boost/weak_ptr.hpp>

using std::string;
using boost::weak_ptr;

class IImport;

class Loader
{
public:
    virtual ~Loader() {}

public:
    void setTranslator(weak_ptr<IImport> wptrTranslator);

    virtual bool loadFrom(const string &fileName) = 0;
    virtual bool saveTo(const string &fileName) = 0;

protected:
    weak_ptr<IImport> m_wptrTranslator;
};

#endif //__LOADER_H__
