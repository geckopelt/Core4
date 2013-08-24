#include <io.h>
#include <sstream>
#include "Win32/Win32App.hxx"
#include "Logging/TextFileLogger.hxx"
#include "Logging/Logger.hxx"
#include "Render/win32/Direct3DRender.hxx"
#include "Utils/StringUtils.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------------------------------------
    Win32App::Win32App() :
        m_active(true), 
        m_hWnd(0)
    {
    }

    //------------------------------------------------------------------------------------------------------------
    void Win32App::init(HWND parent)
    {
        m_hWnd = parent;
        App::init();
        
        // TODO: initialize everything here
        
        ShowCursor(FALSE);
        m_prevUpdate = ::timeGetTime();
    }

    //------------------------------------------------------------------------------------------------------------
    void Win32App::render()
    {
        App::render();

        // TMP
        static unsigned long prevUpdate = ::timeGetTime();

        if (::timeGetTime() - prevUpdate > 1000)
        {
            ::SetWindowTextA(m_hWnd, (StringUtils::intToString(m_renderSystem->getStats().getFPS()) + " fps").c_str());
            prevUpdate = ::timeGetTime();
        }
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
    IRenderSystem * Win32App::createRenderSystem()
    {
        return new Direct3DRender(m_hWnd);
    }

    //------------------------------------------------------------------------------------------------------------
    Win32App::~Win32App()
    {
    }
} // namespace Core4
