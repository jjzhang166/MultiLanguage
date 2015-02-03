#ifndef __TXT_LOADER_H__
#define __TXT_LOADER_H__

#include "../Loader.h"

class TXTLoader : public Loader
{
public:
    virtual bool loadFrom(const string &fileName);
    virtual bool saveTo(const string &fileName);
};

#endif //__TXT_LOADER_H__
