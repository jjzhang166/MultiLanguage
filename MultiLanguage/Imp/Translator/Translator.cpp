#include "Translator.h"
#include <boost/make_shared.hpp>
#include "Concrete/TwoLevelMapTranslator.h"
#include "Concrete/TranslatorTrace.h"

boost::shared_ptr<Translator> Translator::make()
{
#ifdef ENABLE_TRANSLATOR_TRACE
    return boost::make_shared<TranslatorTrace>(
            boost::make_shared<TwoLevelMapTranslator>()
            );
#else
    return boost::make_shared<TwoLevelMapTranslator>();
#endif
}
