#ifndef __TRANSLATOR_H__
#define __TRANSLATOR_H__

#include <boost/shared_ptr.hpp>
#include "IImport.h"
#include "ITranslate.h"

class Translator : public IImport
                 , public ITranslate
{
public:
    static boost::shared_ptr<Translator> make();
    virtual ~Translator() {}
};

#endif //__TRANSLATOR_H__
