#include <fstream>
#include <boost/test/unit_test.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>

#include "../MultiLanguage/Imp/Translator/Translator.h"
#include "../MultiLanguage/Imp/Loader/Concrete/TXTLoader.h"

struct TXTLoaderLoadSuite
{
    bool prepareXmlFile()
    {
        string context = \
            "[main]\n"
            "AA=XXXX\n"
            "BB=YYYY\n"
            "CC=ZZZZ\n"
            "\n"
            "[ui]\n"
            "AA=MMMM\n"
            "\n"
            "[touch]\n"
            "AA=FFFF\n"
            "[]\n"
            "New\\x0aLine=Hello,\\x0aJohn\n";
        std::ofstream ofs;
        ofs.open(fileName.c_str());
        if (!ofs)
            return false;
        ofs << context;
        ofs.close();
        return true;
    }

    TXTLoaderLoadSuite()
        : fileName("txt_loader_test.xml")
    {
        sptrTranslator = Translator::make();
        sptrTXTLoader = boost::make_shared<TXTLoader>();
        sptrTXTLoader->setTranslator(sptrTranslator);

        prepareXmlFile();
    }

    ~TXTLoaderLoadSuite()
    {
        using namespace boost::filesystem;
        remove(path(fileName));
    }

    boost::shared_ptr<TXTLoader> sptrTXTLoader;
    boost::shared_ptr<Translator> sptrTranslator;
    string fileName;
};

BOOST_AUTO_TEST_SUITE(txt_load)

BOOST_FIXTURE_TEST_CASE(load, TXTLoaderLoadSuite)
{
    sptrTXTLoader->loadFrom(fileName);
    BOOST_CHECK_EQUAL(sptrTranslator->translate("AA", "main"), "XXXX");
    BOOST_CHECK_EQUAL(sptrTranslator->translate("aa", "main"), "aa");
    BOOST_CHECK_EQUAL(sptrTranslator->translate("BB", "main"), "YYYY");
    BOOST_CHECK_EQUAL(sptrTranslator->translate("AA", "ui"), "MMMM");
    BOOST_CHECK_EQUAL(sptrTranslator->translate("AA", "touch"), "FFFF");
    BOOST_CHECK_EQUAL(sptrTranslator->translate("New\nLine", ""), "Hello,\nJohn");
}

BOOST_AUTO_TEST_SUITE_END()
