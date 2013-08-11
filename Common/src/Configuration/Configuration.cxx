#include "Configuration/Configuration.hxx"

namespace Core4
{
    // Default values
    //------------------------------------------------------------------------------
    Configuration::Configuration() : m_screenWidth(640), m_screenHeight(480), m_bpp(16), m_windowed(true)
    {
        m_logPath = ".\\log.txt";
        m_appName = "Core4";
    }

    //------------------------------------------------------------------------------
    const size_t Configuration::screenWidth() const   
    { 
        return m_screenWidth; 
    }

    //------------------------------------------------------------------------------
	const size_t Configuration::screenHeight() const   
    { 
        return m_screenHeight; 
    }

    //------------------------------------------------------------------------------
    const size_t Configuration::getBpp() const
    {
        return m_bpp;
    }

    //------------------------------------------------------------------------------
	const std::string & Configuration::getAppName() const 
    { 
        return m_appName; 
    }

    //------------------------------------------------------------------------------
    const std::string & Configuration::getLogPath() const
    {
        return m_logPath;
    }

    //------------------------------------------------------------------------------
    bool Configuration::isWindowed() const
    {
        return m_windowed;
    }

    //------------------------------------------------------------------------------
    void Configuration::setScreenDimensions(size_t width, size_t height)
    {
        m_screenWidth = width;
        m_screenHeight = height;
    }

    //------------------------------------------------------------------------------
    void Configuration::setBpp(size_t bpp)
    {
        m_bpp = bpp;
    }

    //------------------------------------------------------------------------------
    void Configuration::setAppName(const std::string & appName)
    {
        m_appName = appName;
    }

    //------------------------------------------------------------------------------
    void Configuration::setLogPath(const std::string & logPath)
    {
        m_logPath = logPath;
    }

    //------------------------------------------------------------------------------
    void Configuration::setWindowed(bool windowed)
    {
        m_windowed = windowed;
    }
} // Core4