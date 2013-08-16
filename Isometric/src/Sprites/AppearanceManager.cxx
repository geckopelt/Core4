#include "Utils/Guards.hxx"
#include "Sprites/AppearanceManager.hxx"

namespace Core4
{
    //--------------------------------------------------------------------------------------------------------
    const AppearanceManager::Appearance & AppearanceManager::getAppearance(const std::string & name) const
    {
        Appearances::const_iterator it = m_appearances.find(name);
        CORE4_CHECK(it != m_appearances.end(), "Unknown appearance: \"" + name + "\"");
        return it->second;
    }

    //--------------------------------------------------------------------------------------------------------
    bool AppearanceManager::appearanceExists(const std::string & name) const
    {
        return (m_appearances.find(name) != m_appearances.end());
    }

    //--------------------------------------------------------------------------------------------------------
    void AppearanceManager::addAppearance(const std::string & name, const AppearanceManager::Appearance & appearance)
    {
        m_appearances[name] = appearance;
    }

    //--------------------------------------------------------------------------------------------------------
    void AppearanceManager::clear()
    {
        m_appearances.clear();
    }
} // namespace Core4

