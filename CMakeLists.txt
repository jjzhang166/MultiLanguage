cmake_minimum_required(VERSION 2.6)

include_directories(/usr/local/boost_1_57_0/include)
link_directories(/usr/local/boost_1_57_0/lib)

set(multi_language_src
    ./MultiLanguage/Imp/Translator/Concrete/TwoLevelMapTranslator.cpp
    ./MultiLanguage/Imp/Translator/Concrete/TranslatorTrace.cpp
    ./MultiLanguage/Imp/Translator/Translator.cpp
    ./MultiLanguage/Imp/Loader/Concrete/XMLLoader.cpp
    ./MultiLanguage/Imp/Loader/Concrete/TXTLoader.cpp
    ./MultiLanguage/Imp/Loader/Concrete/Util.cpp
    ./MultiLanguage/Imp/Loader/Loader.cpp
    ./MultiLanguage/Imp/MultiLanguageImp.cpp
    ./MultiLanguage/MultiLanguage.cpp
    )

add_library(MultiLanguage ${multi_language_src})
target_link_libraries(MultiLanguage
    boost_system
    boost_filesystem
    )

set(unit_test_src
    ./test/test_MultiLanguageImp.cpp
    ./test/test_TXTLoader.cpp
    ./test/test_main.cpp
    ./test/test_XMLLoader.cpp
    ./test/test_TwoLevelMapTranslator.cpp
    )

add_executable(unit_test ${unit_test_src})
target_link_libraries(unit_test MultiLanguage)
