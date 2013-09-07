#pragma once

#include <string>
#include "UI/Font/FontParser.hxx"

class FontParserTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(FontParserTests);
        CPPUNIT_TEST(simpleLineTest);
        CPPUNIT_TEST(fontInfoParseTest);
    CPPUNIT_TEST_SUITE_END();

    void simpleLineTest()
    {
        const std::string simpleLine("foo bar=1 baz=42 titi=\"toto\"");
        std::string tagName;
        FontParser::FontOptions options = FontParser::parseFontOptionsLine(simpleLine, tagName);
        CPPUNIT_ASSERT(3 == options.size());
        CPPUNIT_ASSERT(tagName == "foo");
        CPPUNIT_ASSERT(options["bar"] == "1");
        CPPUNIT_ASSERT(options["baz"] == "42");
        CPPUNIT_ASSERT(options["titi"] == "toto");
    }

    void fontInfoParseTest()
    {
        const std::string fontInfo("info face=\"Arial\" size=32 bold=0 italic=0 charset=\"\" unicode=1 aa spacing=1,2 outline=0");
        FontInfo info = FontParser::parseFontInfo(fontInfo);
        CPPUNIT_ASSERT(info.getFace() == "Arial");
        CPPUNIT_ASSERT(info.getSize() == 32);
        CPPUNIT_ASSERT(info.getSpacing().x() == 1);
        CPPUNIT_ASSERT(info.getSpacing().y() == 2);

    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(FontParserTests);

