#pragma once

#define _USE_32BIT_TIME_T
#include <stdlib.h>

/// @file App.hxx
/// @brief Platform-independent application stuff

namespace Core4
{
    /// Platform-independent application stuff.
    class App
    {
    public:
        /// Ctor.
        App();

        virtual ~App();
        
        /// Init Core4 application.
        void init();

        /// Deinit Core4 application.
        void deinit();

        /// Update and render everything.
        void render();

        /// Update previous update time.
        virtual unsigned long getCurrTime() const = 0;
    protected:
        unsigned long m_prevUpdate;
    };
} // namespace Core4
