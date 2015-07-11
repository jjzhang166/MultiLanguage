#define BOOST_TEST_MODULE TwoLevelMapTranslator
#include <boost/test/unit_test.hpp>
#include <boost/assign.hpp>
#include <boost/foreach.hpp>
#include "../MultiLanguage/Imp/Translator/Concrete/TwoLevelMapTranslator.h"

BOOST_AUTO_TEST_SUITE(import_export)

bool operator == (const TransItem &lhs, const TransItem &rhs)
{
    return (lhs.origin_text == rhs.origin_text &&
            lhs.trans_text == rhs.trans_text &&
            lhs.domain == rhs.domain);
}

BOOST_AUTO_TEST_CASE(import)
{
    list<TransItem> import_dict;

    boost::assign::push_back(import_dict)(TransItem("AA", "XXXXX", "1"))\
                                         (TransItem("BB", "YYXXX", "1"))\
                                         (TransItem("CC", "XXYYZZ", "2"))\
                                         (TransItem("AA", "DDDDD", "2"));
    TwoLevelMapTranslator translator;
    list<DomainInhertUnit> inhert_list;

    translator.importItems(import_dict, inhert_list);

    list<TransItem> export_dict;
    translator.exportItems(export_dict);

    BOOST_CHECK_EQUAL(import_dict.size(), export_dict.size());

    BOOST_FOREACH(const TransItem &import_item, import_dict) {
        bool isThisFound = false;
        BOOST_FOREACH(const TransItem &export_item, export_dict) {
            if (import_item == export_item) {
                isThisFound = true;
                break;
            }
        }
        if (!isThisFound) {
            BOOST_ERROR("Not all item found.");
            break;
        }
    }
}

BOOST_AUTO_TEST_SUITE_END()

/////////////////////////////////////////////////////////////////////

struct TranslateFixture
{
    TranslateFixture()
    {
        list<TransItem> import_dict;
        boost::assign::push_back(import_dict)\
                (TransItem("AA", "XXXXX", "1"))\
                (TransItem("BB", "YYXXX", "1"))\
                (TransItem("CC", "XXYYZZ", "2"))\
                (TransItem("AA", "DDDDD", "2"));
        
        list<DomainInhertUnit> inhert_list;
        translator.importItems(import_dict, inhert_list);
    }

    ~TranslateFixture()
    {

    }

    TwoLevelMapTranslator translator;
};

BOOST_FIXTURE_TEST_SUITE(translate, TranslateFixture)

BOOST_AUTO_TEST_CASE(translate)
{
    BOOST_CHECK_EQUAL(translator.translate("AA", ""), "AA");
    BOOST_CHECK_EQUAL(translator.translate("AA", "1") , "XXXXX");
    BOOST_CHECK_EQUAL(translator.translate("BB", "1") , "YYXXX");
    BOOST_CHECK_EQUAL(translator.translate("AA", "2") , "DDDDD");
    BOOST_CHECK_EQUAL(translator.translate("AA", "3") , "AA");
    BOOST_CHECK_EQUAL(translator.translate("FF", "") , "FF");
}

BOOST_AUTO_TEST_CASE(reverse_translator)
{
    BOOST_CHECK_EQUAL(translator.reverse_translate("XXXXX", "1") , "AA");
    BOOST_CHECK_EQUAL(translator.reverse_translate("XXYYZZ", "2") , "CC");
    BOOST_CHECK_EQUAL(translator.reverse_translate("DDDDD", "1") , "DDDDD");
    BOOST_CHECK_EQUAL(translator.reverse_translate("DDDDD", "2") , "AA");
    BOOST_CHECK_EQUAL(translator.reverse_translate("JJJ", "") , "JJJ");
}

BOOST_AUTO_TEST_SUITE_END()
