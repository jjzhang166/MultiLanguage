#include "Loader.h"
#include "../Translator/IImportAndExport.h"

void Loader::setTranslator(weak_ptr<IImportAndExport> wptrTranslator)
{
    m_wptrTranslator = wptrTranslator;
}
