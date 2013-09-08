#pragma once

/// @file Configuration.hxx
/// @brief Core4 engine settings

#include <string>
#include "Utils/Singleton.hxx"

namespace Core4
{
    /// Core4 configuration options
    class Configuration : public Singleton<Configuration>
    {
    public:
        /// Default ctor, initializes all the settings.
        Configuration();

        /// Get screen width.
        /// @return screen width in pixels.
	    const size_t screenWidth() const;

        /// Get screen height.
        /// @return screen height in pixels.
	    const size_t screenHeight() const;

        /// Get bits per pixel setting.
        /// @return color depth in bits per pixel.
        const size_t getBpp() const;

        /// Get app name.
        /// @return App name.
	    const std::string & getAppName() const;

        /// Get log file pathname.
        /// @return Log file pathname.
        const std::string & getLogPath() const;

        /// Get resources root folder.
        /// @return resources root folder.
        const std::string & getResourcesRoot() const;

        /// Set resources root folder.
        /// @param folder Root folder.
        void setResourcesRoot(const std::string & folder);

        /// Check whether application is windowed.
        /// @return true if windowed.
        bool isWindowed() const;

        /// Set screen resolution.
        /// @param width Screen width in pixels
        /// @param height Screen height in pixels
        void setScreenDimensions(size_t width, size_t height);

        /// Set bits per pixel.
        /// @param bpp Bits per pixel.
        void setBpp(size_t bpp);

        /// Set application name.
        /// @param appName Application name.
        void setAppName(const std::string & appName);

        /// Set log pathname.
        /// @param logPath Full path to log file.
        void setLogPath(const std::string & logPath);

        /// Set windowed flag.
        /// @param windowed Is application windowed. 
        void setWindowed(bool windowed);
    private:
        size_t            m_screenWidth;
        size_t            m_screenHeight;
        std::string       m_appName;
        std::string       m_logPath;
        size_t            m_bpp;
        bool              m_windowed;
        std::string       m_resourcesRoot;
    };
} // namespace Core4