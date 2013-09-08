#include <algorithm>
#include <fstream>
#include <iostream>
#include "Utils/Guards.hxx"
#include "Utils/StringUtils.hxx"
#include "Logging/LogHelpers.hxx"
#include "Serialization/TypeConverters.hxx"
#include "UI/Font/FontParser.hxx"

namespace
{
    bool shouldBeSkipped(char c)
    {
        return '\"' == c;
    }

    const std::string & getOption(const std::map<std::string, std::string> & options, const std::string & name)
    {
        using namespace Core4;
        std::map<std::string, std::string>::const_iterator it = options.find(name);
        CORE4_CHECK(it != options.end(), "Font option missing: \"" + name + "\"");
        return it->second;
    }
}

namespace Core4
{
    //--------------------------------------------------------------------------------------------
    FontParser::FontOptions FontParser::parseFontOptionsLine(const std::string & str, std::string & tagName)
    {
        std::vector<std::string> parts;
        StringUtils::splitString(str, " ", parts);

        tagName.clear();
        if (parts.empty())
            return FontParser::FontOptions();

        tagName = parts[0];

        FontParser::FontOptions options;

        std::vector<std::string>::iterator it = ++parts.begin();
        while (it != parts.end())
        {
            std::string & part = (*it);

            if (!part.empty())
            {
                part.erase(std::remove_if(part.begin(), part.end(), shouldBeSkipped), part.end());

                std::vector<std::string> optionParts;
                StringUtils::splitString(part, "=", optionParts);
                if (2 == optionParts.size())
                {
                    options[optionParts[0]] = optionParts[1];
                }
            }
            it++;
        }
        return options;
    }

    //--------------------------------------------------------------------------------------------
    FontInfo FontParser::parseFontInfo(const FontOptions & options)
    {
        FontInfo fontInfo;
        fontInfo.setFace(getOption(options, "face"));
        
        size_t size(0);
        TypeConverters::fromString(getOption(options, "size"), size);
        fontInfo.setSize(size);

        float spacingX(0.f);
        float spacingY(0.f);

        std::vector<std::string> spacingParts;
        StringUtils::splitString(getOption(options, "spacing"), ",", spacingParts);
        CORE4_CHECK(2 == spacingParts.size(), "Invalid spacing");

        TypeConverters::fromString(spacingParts[0], spacingX);
        TypeConverters::fromString(spacingParts[1], spacingY);

        fontInfo.setSpacing(Vector2(spacingX, spacingY));
        return fontInfo;
    }

    //--------------------------------------------------------------------------------------------
    FontCommon FontParser::parseCommonInfo(const FontOptions & options)
    {
        std::string tagName;

        float lineHeight(0);
        TypeConverters::fromString(getOption(options, "lineHeight"), lineHeight);

        FontCommon fontCommon;
        fontCommon.setLineHeight(lineHeight);

        return fontCommon;
    }

    //--------------------------------------------------------------------------------------------
    FontChar FontParser::parseChar(const FontOptions & options)
    {
        FontChar fc;

        size_t id(0);
        TypeConverters::fromString(getOption(options, "id"), id);
        fc.setChar(static_cast<wchar_t>(id));

        float x(0.f), y(0.f), width(0.f), height(0.f);
        TypeConverters::fromString(getOption(options, "x"), x);
        TypeConverters::fromString(getOption(options, "y"), y);
        TypeConverters::fromString(getOption(options, "width"), width);
        TypeConverters::fromString(getOption(options, "height"), height);
        fc.setRect(Rect(Vector2(x, y), Vector2(width, height)));

        float offsetX(0.f), offsetY(0.f), advanceX(0.f);
        TypeConverters::fromString(getOption(options, "xoffset"), offsetX);
        TypeConverters::fromString(getOption(options, "yoffset"), offsetY);
        TypeConverters::fromString(getOption(options, "xadvance"), advanceX);
        fc.setOffset(Vector2(offsetX, offsetY));
        fc.setAdvanceX(advanceX);

        size_t page(0);
        TypeConverters::fromString(getOption(options, "page"), page);
        fc.setPageNumber(page);

        return fc;
    }

    //--------------------------------------------------------------------------------------------
    void FontParser::parseKerning(const FontOptions & options, wchar_t & left, wchar_t & right, float & kerning)
    {
        // TODO: So crappy. We need a better string-to-something converter.
        size_t first(0), second(0);
        TypeConverters::fromString(getOption(options, "first"), first);
        TypeConverters::fromString(getOption(options, "second"), second);
        TypeConverters::fromString(getOption(options, "amount"), kerning);

        left = first;
        right = second;
    }

    //--------------------------------------------------------------------------------------------
    void FontParser::parsePage(const FontOptions & options, size_t & pageNumber, std::string & textureName)
    {   
        TypeConverters::fromString(getOption(options, "id"), pageNumber);
        TypeConverters::fromString(getOption(options, "file"), textureName);
    }

    //--------------------------------------------------------------------------------------------
    Font FontParser::parseFont(const std::string & filename)
    {
        CORE4_LOG_SECTION("Loading font: \"" + filename + "\"");
        Font font;
        std::ifstream f(filename);
        CORE4_CHECK(f.is_open(), "Can't open \"" + filename + "\"");
        while (f.good())
        {
            std::string line;
            std::getline(f, line);

            std::string tagName;
            FontParser::FontOptions options = parseFontOptionsLine(line, tagName); 
        
            if (tagName == "info")
            {
                font.m_info = parseFontInfo(options);
            }
            else
            if (tagName == "common")
            {
                font.m_common = parseCommonInfo(options);
            }
            else
            if (tagName == "char")
            {
                FontChar fc = parseChar(options);
                font.m_chars[fc.getChar()] = fc;
            }
            else
            if (tagName == "kerning")
            {
                wchar_t left(0), right(0);
                float kerning(0);
                parseKerning(options, left, right, kerning);
                font.m_kerning.addKerningInfo(left, right, kerning);
            }
            else
            if (tagName == "page")
            {
                std::string textureName;
                size_t pageNumber(0);
                parsePage(options, pageNumber, textureName);
                font.m_pages[pageNumber] = textureName;
            }
        }
        f.close();
        return font;
    }
}
