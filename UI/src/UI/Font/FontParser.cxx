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

            if (part.empty())
                continue;

            part.erase(std::remove_if(part.begin(), part.end(), shouldBeSkipped), part.end());

            std::vector<std::string> optionParts;
            StringUtils::splitString(part, "=", optionParts);
            if (2 == optionParts.size())
            {
                options[optionParts[0]] = optionParts[1];
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
        CORE4_CHECK("info" == tagName, "Not an info line");

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
        return FontCommon();
    }

    //--------------------------------------------------------------------------------------------
    FontChar FontParser::parseChar(const std::string & str)
    {
        return FontChar();
    }

    //--------------------------------------------------------------------------------------------
    FontKerningInfo FontParser::parseKerning(const std::string & str)
    {
        return FontKerningInfo();
    }

    //--------------------------------------------------------------------------------------------
    void FontParser::parsePage(const std::string & str, size_t & pageNumber, std::string & textureName)
    {
    }
}
