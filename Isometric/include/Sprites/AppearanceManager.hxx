#pragma once

/// @file AppearanceManager.hxx
/// @brief Appearance manager implementation.

#include <map>
#include "Utils/Singleton.hxx"
#include "Sprites/IAppearanceManager.hxx"

namespace Core4
{
    /// Appearance manager implementation.
    class AppearanceManager : 
        public IAppearanceManager,
        public Singleton<AppearanceManager>
    {
    public:
        /// @see IAppearanceManager
        const Appearance & getAppearance(const std::string & name) const;

        /// @see IAppearanceManager
        bool appearanceExists(const std::string & name) const;

        /// @see IAppearanceManager
        void addAppearance(const std::string & name, const Appearance & appearance);
        
        /// @see IAppearanceManager
        void clear();
    private:
        typedef std::map< std::string, std::vector<size_t> > Appearances;
        Appearances m_appearances;
    };
} // namespace Core4
