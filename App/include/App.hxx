#pragma once

/// @file App.hxx
/// @brief Platform-independent application stuff

#define _USE_32BIT_TIME_T
#include <stdlib.h>

#include "Render/IRenderSystem.hxx"

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

        /// Create a render system.
        virtual IRenderSystem * createRenderSystem() = 0;
    protected:
        unsigned long m_prevUpdate;
        IRenderSystem * m_renderSystem;
    };
} // namespace Core4
