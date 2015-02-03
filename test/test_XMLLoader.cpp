#include <fstream>
#include <boost/test/unit_test.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>

#include "../MultiLanguage/Imp/Translator/Translator.h"
#include "../MultiLanguage/Imp/Loader/Concrete/XMLLoader.h"

struct XMLLoaderLoadSuite
{
    bool prepareXmlFile()
    {
        string context = \
            "<language id=\"en\">\n"
            "  <prefix id=\"main\">\n"
            "    <item orgin=\"AA\" trans=\"XXXX\">\n"
            "    <item orgin=\"BB\" trans=\"YYYY\">\n"
            "    <item orgin=\"CC\" trans=\"ZZZZ\">\n"
            "  </prefix>\n"
            "  <prefix id=\"ui\">\n"
            "    <item orgin=\"AA\" trans=\"MMMM\">\n"
            "  </prefix>\n"
            "  <prefix id=\"touch\">\n"
            "    <item orgin=\"AA\" trans=\"FFFF\">\n"
            "  </prefix>\n"
            "</language>\n";
        std::ofstream ofs;
        ofs.open(fileName.c_str());
        if (!ofs)
            return false;
        ofs << context;
        ofs.close();
        return true;
    }

    XMLLoaderLoadSuite()
        : fileName("loader_test.xml")
    {
        sptrTranslator = Translator::make();
        sptrXMLLoader = boost::make_shared<XMLLoader>();
        sptrXMLLoader->setTranslator(sptrTranslator);

        prepareXmlFile();
    }

    ~XMLLoaderLoadSuite()
    {
        using namespace boost::filesystem;
        remove(path(fileName));
    }

    boost::shared_ptr<XMLLoader> sptrXMLLoader;
    boost::shared_ptr<Translator> sptrTranslator;
    string fileName;
};

BOOST_AUTO_TEST_SUITE(load)

BOOST_FIXTURE_TEST_CASE(load, XMLLoaderLoadSuite)
{
    sptrXMLLoader->loadFrom(fileName);
    BOOST_CHECK_EQUAL(sptrTranslator->translate("AA", "main"), "XXXX");
    BOOST_CHECK_EQUAL(sptrTranslator->translate("aa", "main"), "aa");
    BOOST_CHECK_EQUAL(sptrTranslator->translate("BB", "main"), "YYYY");
    BOOST_CHECK_EQUAL(sptrTranslator->translate("AA", "ui"), "MMMM");
    BOOST_CHECK_EQUAL(sptrTranslator->translate("AA", "touch"), "FFFF");
}

BOOST_AUTO_TEST_SUITE_END()
