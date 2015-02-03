#-------------------------------------------------
#
# Project created by QtCreator 2015-01-31T17:20:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MultiLanguage
TEMPLATE = app


SOURCES +=\
        MultiLanguage/MultiLanguage.cpp \
        MultiLanguage/Imp/Loader/Loader.cpp \
        MultiLanguage/Imp/Loader/Concrete/XMLLoader.cpp \
        MultiLanguage/Imp/Loader/Concrete/TXTLoader.cpp \
        MultiLanguage/Imp/MultiLanguageImp.cpp \
        MultiLanguage/Imp/Translator/Concrete/TwoLevelMapTranslator.cpp \
    test/test_TwoLevelMapTranslator.cpp \
    test/test_main.cpp \
    test/test_XMLLoader.cpp \
    MultiLanguage/Imp/Translator/Translator.cpp \
    test/test_TXTLoader.cpp \
    test/test_MultiLanguageImp.cpp


HEADERS  += \
        MultiLanguage/Imp/MultiLanguageImp.h \
        MultiLanguage/Imp/Loader/Loader.h \
        MultiLanguage/Imp/Loader/Concrete/XMLLoader.h \
        MultiLanguage/Imp/Loader/Concrete/TXTLoader.h \
        MultiLanguage/Imp/Translator/Translator.h \
        MultiLanguage/Imp/Translator/ITranslate.h \
        MultiLanguage/Imp/Translator/IImportAndExport.h \
        MultiLanguage/MultiLanguage.h \
        MultiLanguage/Imp/Translator/Concrete/TwoLevelMapTranslator.h


FORMS    +=

#LIBS = -lboost_unit_test_framework
LIBS = -lboost_system -lboost_filesystem
