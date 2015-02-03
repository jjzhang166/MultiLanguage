#ifndef __XML_LOADER_H__
#define __XML_LOADER_H__

#include "../Loader.h"

class XMLLoader : public Loader
{
public:    
    virtual bool loadFrom(const string &fileName);
    virtual bool saveTo(const string &fileName);
};

#endif //__XML_LOADER_H__
