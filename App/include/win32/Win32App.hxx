#pragma once

/// @file Win32App.hxx
/// @brief A Win32 application class.

#include "Utils/Singleton.hxx"
#include "App.hxx"
#include "Win32/Win32Common.hxx"

namespace Core4
{
    /// Core4 engine Win32 app implementation
    class Win32App : public Core4::Singleton<Win32App>, public App
    {
    public:
        /// Ctor.
        Win32App();

        /// Init Win32 application.
        void init(HWND parent);

        /// Render everything.
        void render();

        /// Dtor.
        virtual ~Win32App();

        /// Is window active?
        /// @return true if active.
	    bool isActive() const;

        /// Activate or deactivatewindow.
        /// @bool active 
	    void setActive(bool active);

        /// @see App
        unsigned long getCurrTime() const;
    private:
        bool              m_active;
    };

} // namespace Core4