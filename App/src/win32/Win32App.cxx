#include <io.h>
#include <sstream>
#include "Win32/Win32App.hxx"
#include "Logging/TextFileLogger.hxx"
#include "Logging/Logger.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------------------------------------
    Win32App::Win32App() :
        m_active(false)
    {
    }

    //------------------------------------------------------------------------------------------------------------
    void Win32App::init(HWND parent)
    {
        App::init();
        
        // TODO: initialize everything here
        
        ShowCursor(FALSE);
        m_prevUpdate = ::timeGetTime();
    }

    //------------------------------------------------------------------------------------------------------------
    void Win32App::render()
    {
        App::render();

        // TODO: platform-specific render
        /* TODO
        if (NULL != m_renderSystem)
        {
            m_renderSystem->render();
        }
        */
    }

    //------------------------------------------------------------------------------------------------------------
    bool Win32App::isActive() const
    {
        return m_active;
    }

    //------------------------------------------------------------------------------------------------------------
    void Win32App::setActive(bool active)
    {
        m_active = active;
    }

    //------------------------------------------------------------------------------------------------------------
    unsigned long Win32App::getCurrTime() const
    {
        return (unsigned long)::timeGetTime();
    }

    //------------------------------------------------------------------------------------------------------------
    Win32App::~Win32App()
    {
    }
} // namespace Core4
