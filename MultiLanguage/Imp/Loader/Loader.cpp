#include "Loader.h"
#include "../Translator/IImport.h"

void Loader::setTranslator(weak_ptr<IImport> wptrTranslator)
{
    m_wptrTranslator = wptrTranslator;
}
