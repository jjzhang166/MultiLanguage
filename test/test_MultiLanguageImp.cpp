#include <fstream>
#include <boost/test/unit_test.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>

#include "../MultiLanguage/Imp/MultiLanguageImp.h"

using namespace boost;
using namespace std;

struct MultiLanguageImpTestXMLSuit
{
    void prepare_ch()
    {
        ofstream ofs;
        ofs.open("language_ch.xml");
        if (!ofs)
            return;

        string context = \
                "<language id=\"ch\">\n"
                "   <prefix id=\"meas\">\n"
                "       <item origin=\"GA\" trans=\"Yun Zhou\">\n"
                "       <item origin=\"EDD\" trans=\"Yu Chan Qi\">\n"
                "   </prefix>\n"
                "   <prefix id=\"touch\">\n"
                "       <item origin=\"EDD\" trans=\"Yu&#xaChan&#xaQi\">\n"
                "   </prefix>\n"
                "</language>";
        ofs << context;
        ofs.close();
    }

    void prepare_en()
    {
        ofstream ofs;
        ofs.open("language_en.xml");
        if (!ofs)
            return;

        string context = \
                "<language id=\"en\">\n"
                "   <prefix id=\"meas\">\n"
                "       <item origin=\"GA\" trans=\"Gravida\">\n"
                "       <item origin=\"EDD\" trans=\"Expected date\">\n"
                "   </prefix>\n"
                "   <prefix id=\"touch\">\n"
                "       <item origin=\"EDD\" trans=\"Expected&#xadate\">\n"
                "   </prefix>\n"
                "</language>";
        ofs << context;
        ofs.close();

    }

    MultiLanguageImpTestXMLSuit()
    {
        //! Prepare file: language_en.xml, language_ch.xml
        prepare_en();
        prepare_ch();

        m_sptrMultiLanguage = make_shared<MultiLanguageImp>();
        m_sptrMultiLanguage->setFilePath("./");
        m_sptrMultiLanguage->setFileType("xml");
    }

    ~MultiLanguageImpTestXMLSuit()
    {
        using namespace boost::filesystem;
        remove(path("language_en.xml"));
        remove(path("language_ch.xml"));
    }

    shared_ptr<MultiLanguageImp> m_sptrMultiLanguage;
};

BOOST_FIXTURE_TEST_SUITE(multi_language_xml, MultiLanguageImpTestXMLSuit)

BOOST_AUTO_TEST_CASE(set_language)
{
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->setLanguage("en"), true);
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->setLanguage("fch"), false);
}

BOOST_AUTO_TEST_CASE(translate_en)
{
    m_sptrMultiLanguage->setLanguage("en");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->translate("GA", "meas"), "Gravida");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->translate("EDD", "meas"), "Expected date");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->translate("EDD", "touch"), "Expected\ndate");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->translate("AFI", ""), "AFI");

    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->reverse_translate("Gravida", "meas"), "GA");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->reverse_translate("Expected date", "meas"), "EDD");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->reverse_translate("Expected\ndate", "meas"), "Expected\ndate");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->reverse_translate("Expected\ndate", "touch"), "EDD");
}

BOOST_AUTO_TEST_CASE(translate_ch)
{
    m_sptrMultiLanguage->setLanguage("ch");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->translate("GA", "meas"), "Yun Zhou");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->translate("EDD", "meas"), "Yu Chan Qi");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->translate("EDD", "touch"), "Yu\nChan\nQi");

    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->reverse_translate("Yun Zhou", "meas"), "GA");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->reverse_translate("Yu Chan Qi", "meas"), "EDD");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->reverse_translate("Yu\nChan\nQi", "meas"), "Yu\nChan\nQi");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->reverse_translate("Yu\nChan\nQi", "touch"), "EDD");
}

BOOST_AUTO_TEST_SUITE_END()


struct MultiLanguageImpTestTXTSuit
{
    void prepare_ch()
    {
        ofstream ofs;
        ofs.open("language_ch.txt");
        if (!ofs)
            return;

        string context = \
                "[meas]\n"
                "GA=Yun Zhou\n"
                "EDD=Yu Chan Qi\n"
                "[touch]\n"
                "EDD=Yu\\x0aChan\\x0aQi\n";
        ofs << context;
        ofs.close();
    }

    void prepare_en()
    {
        ofstream ofs;
        ofs.open("language_en.txt");
        if (!ofs)
            return;

        string context = \
                "[meas]\n"
                "GA=Gravida\n"
                "EDD=Expected date\n"
                "[touch]\n"
                "EDD=Expected\\x0adata\n";
        ofs << context;
        ofs.close();

    }

    MultiLanguageImpTestTXTSuit()
    {
        prepare_en();
        prepare_ch();

        m_sptrMultiLanguage = make_shared<MultiLanguageImp>();
        m_sptrMultiLanguage->setFilePath("./");
        m_sptrMultiLanguage->setFileType("txt");
    }

    ~MultiLanguageImpTestTXTSuit()
    {
        //! Remove file
        using namespace boost::filesystem;
        remove(path("language_en.txt"));
        remove(path("language_ch.txt"));
    }

    shared_ptr<MultiLanguageImp> m_sptrMultiLanguage;

};

BOOST_FIXTURE_TEST_SUITE(multi_language_txt, MultiLanguageImpTestTXTSuit)

BOOST_AUTO_TEST_CASE(set_language)
{
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->setLanguage("en"), true);
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->setLanguage("fch"), false);
}

BOOST_AUTO_TEST_CASE(translate_en)
{
    m_sptrMultiLanguage->setLanguage("en");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->translate("GA", "meas"), "Gravida");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->translate("EDD", "meas"), "Expected date");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->translate("EDD", "touch"), "Expected\ndate");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->translate("AFI", ""), "AFI");

    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->reverse_translate("Gravida", "meas"), "GA");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->reverse_translate("Expected date", "meas"), "EDD");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->reverse_translate("Expected\ndate", "meas"), "Expected\ndate");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->reverse_translate("Expected\ndate", "touch"), "EDD");
}

BOOST_AUTO_TEST_CASE(translate_ch)
{
    m_sptrMultiLanguage->setLanguage("ch");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->translate("GA", "meas"), "Yun Zhou");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->translate("EDD", "meas"), "Yu Chan Qi");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->translate("EDD", "touch"), "Yu\nChan\nQi");

    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->reverse_translate("Yun Zhou", "meas"), "GA");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->reverse_translate("Yu Chan Qi", "meas"), "EDD");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->reverse_translate("Yu\nChan\nQi", "meas"), "Yu\nChan\nQi");
    BOOST_CHECK_EQUAL(m_sptrMultiLanguage->reverse_translate("Yu\nChan\nQi", "touch"), "EDD");
}

BOOST_AUTO_TEST_SUITE_END()
