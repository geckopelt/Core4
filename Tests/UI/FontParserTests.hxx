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
        CPPUNIT_TEST(complexFontParserTest);
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
        const std::string commonDesc("common lineHeight=32");
        FontCommon common = FontParser::parseCommonInfo(commonDesc);
        CPPUNIT_ASSERT(common.getLineHeight() == 32.f);
    }

    void fontCharParseTest()
    {
        const std::string charDesc("char id=32   x=21    y=57    width=3     height=1     xoffset=-1    yoffset=31    xadvance=8     page=3  chnl=15");
        FontChar c = FontParser::parseChar(charDesc);
        CPPUNIT_ASSERT(c.getChar() == 32);

        const Rect & rect = c.getRect();
        CPPUNIT_ASSERT(rect.getUpperLeft().x() == 21.f);
        CPPUNIT_ASSERT(rect.getUpperLeft().y() == 57.f);
        CPPUNIT_ASSERT(rect.getSize().x() == 3.f);
        CPPUNIT_ASSERT(rect.getSize().y() == 1.f);
        
        CPPUNIT_ASSERT(c.getOffset().x() == -1.f);
        CPPUNIT_ASSERT(c.getOffset().y() == 31.f);
        CPPUNIT_ASSERT(c.getAdvanceX() == 8.f);
        CPPUNIT_ASSERT(c.getPageNumber() == 3);
    }

    void fontKerningParseTest()
    {
        const std::string kerningDesc("kerning first=87  second=117 amount=-1");
        wchar_t left(0), right(0);
        float kerning(0);
        FontParser::parseKerning(kerningDesc, left, right, kerning);
        CPPUNIT_ASSERT(left == 87);
        CPPUNIT_ASSERT(right == 117);
        CPPUNIT_ASSERT(kerning == -1.f);
    }

    void fontPageParseTest()
    {
        const std::string page("page id=1 file=\"foo.tga\"");
        size_t pageNumber(0);
        std::string textureName;
        FontParser::parsePage(page, pageNumber, textureName);
        CPPUNIT_ASSERT(pageNumber == 1);
        CPPUNIT_ASSERT(textureName == "foo.tga");
    }

    void complexFontParserTest()
    {
        // TODO
        CPPUNIT_ASSERT(false);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(FontParserTests);

