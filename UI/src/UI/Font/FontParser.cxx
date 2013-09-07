#include <algorithm>
#include "Utils/Guards.hxx"
#include "Utils/StringUtils.hxx"
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
    // TODO: pass FontOptions from complex parser!

    //--------------------------------------------------------------------------------------------
    FontParser::FontOptions FontParser::parseFontOptionsLine(const std::string & str, std::string & tagName)
    {
        std::vector<std::string> parts;
        StringUtils::splitString(str, " ", parts);

        CORE4_CHECK(!parts.empty(), "Can't parse \"" + str + "\"");
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
    FontInfo FontParser::parseFontInfo(const std::string & str)
    {
        std::string tagName;
        FontOptions options = parseFontOptionsLine(str, tagName);

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
    FontCommon FontParser::parseCommonInfo(const std::string & str)
    {
        std::string tagName;
        FontOptions options = parseFontOptionsLine(str, tagName);

        float lineHeight(0);
        TypeConverters::fromString(getOption(options, "lineHeight"), lineHeight);

        FontCommon fontCommon;
        fontCommon.setLineHeight(lineHeight);

        return fontCommon;
    }

    //--------------------------------------------------------------------------------------------
    FontChar FontParser::parseChar(const std::string & str)
    {
        FontChar fc;
        FontOptions options = parseFontOptionsLine(str, std::string());

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
    void FontParser::parseKerning(const std::string & str, wchar_t & left, wchar_t & right, float & kerning)
    {
        FontOptions options = parseFontOptionsLine(str, std::string());
        
        // TODO: So crappy. We need a better string-to-something converter.
        size_t first(0), second(0);
        TypeConverters::fromString(getOption(options, "first"), first);
        TypeConverters::fromString(getOption(options, "second"), second);
        TypeConverters::fromString(getOption(options, "amount"), kerning);

        left = first;
        right = second;
    }

    //--------------------------------------------------------------------------------------------
    void FontParser::parsePage(const std::string & str, size_t & pageNumber, std::string & textureName)
    {   
        std::string tagName;
        FontOptions options = parseFontOptionsLine(str, tagName);
        TypeConverters::fromString(getOption(options, "id"), pageNumber);
        TypeConverters::fromString(getOption(options, "file"), textureName);
    }

    //--------------------------------------------------------------------------------------------
    void FontParser::parseFont(const std::string & filename, Font & font)
    {
    }
}
