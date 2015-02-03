#include "Translator.h"
#include <boost/make_shared.hpp>
#include "Concrete/TwoLevelMapTranslator.h"

boost::shared_ptr<Translator> Translator::make()
{
    return boost::make_shared<TwoLevelMapTranslator>();
}
