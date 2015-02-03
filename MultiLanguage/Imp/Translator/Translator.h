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

public:
    virtual void importItems(const list<TransItem> &items) = 0;
    virtual void exportItems(list<TransItem> &items) const = 0;

public:
    virtual string translate(const string &origin_text, const string &prefix) const = 0;
    virtual string reverse_translate(const string &trans_text, const string &prefix) const = 0;
};

#endif //__TRANSLATOR_H__
