#include "Configuration/Configuration.hxx"
#include "Utils/Guards.hxx"
#include "UI/Font/FontManager.hxx"
#include "UI/Font/FontParser.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------
    void FontManager::addFont(const std::string & fontName, const std::string & filename)
    {
        const std::string fontFolder(Configuration::getSingleton().getResourcesRoot() + "/fonts/");
        Font font = FontParser::parseFont(fontFolder + filename);
        m_fonts[fontName] = font;
    }

    //------------------------------------------------------------------------------
    const Font & FontManager::getFont(const std::string & fontName) const
    {
        std::map<std::string, Font>::const_iterator it = m_fonts.find(fontName);
        CORE4_CHECK(it != m_fonts.end(), "Font not loaded: \"" + fontName + "\"");
        return it->second;
    }
} // namespace Core4