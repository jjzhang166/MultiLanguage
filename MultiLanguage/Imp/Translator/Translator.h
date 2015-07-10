#ifndef __TRANSLATOR_H__
#define __TRANSLATOR_H__

#include <boost/shared_ptr.hpp>
#include "IImportAndExport.h"
#include "ITranslate.h"

class Translator : public IImportAndExport
                 , public ITranslate
{
public:
    static boost::shared_ptr<Translator> make();
    virtual ~Translator() {}
};

#endif //__TRANSLATOR_H__
