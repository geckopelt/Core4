#pragma once

#include <string>
#include "UI/Font/FontParser.hxx"

class FontParserTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(FontParserTests);
        CPPUNIT_TEST(simpleLineTest);
        CPPUNIT_TEST(fontInfoParseTest);
        CPPUNIT_TEST(fontCommonInfoParseTest);
        CPPUNIT_TEST(fontCharParseTest);
        CPPUNIT_TEST(fontKerningParseTest);
        CPPUNIT_TEST(fontPageParseTest);

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

    void fontCommonInfoParseTest()
    {
        const std::string common("common lineHeight=32");
        // FontCommon common
    }

    void fontCharParseTest()
    {
        const std::string charDesc("char id=32   x=21    y=57    width=3     height=1     xoffset=-1    yoffset=31    xadvance=8     page=0  chnl=15");
    }

    void fontKerningParseTest()
    {
        const std::string kerningDesc("kerning first=87  second=117 amount=-1");
    }

    void fontPageParseTest()
    {
        const std::string page("page id=0 file=\"TestFont_0.tga\"");
    }

    // TODO
    // FontCommon FontParser::parseCommonInfo(const std::string & str)
    // FontChar FontParser::parseChar(const std::string & str)
    // FontKerningInfo FontParser::parseKerning(const std::string & str)
    // void FontParser::parsePage(const std::string & str, size_t & pageNumber, std::string & textureName)
};

CPPUNIT_TEST_SUITE_REGISTRATION(FontParserTests);

