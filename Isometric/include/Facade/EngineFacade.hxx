#pragma once

/// @file EngineFacade.hxx
/// @brief Core4 engine facade.

#include "Utils/Singleton.hxx"
#include "Render/IRenderSystem.hxx"
#include "Input/IInputListener.hxx"
#include "Location/LocationMap.hxx"
#include "Location/LocationRenderer.hxx"
#include "Tiles/MouseMap.hxx"

namespace Core4
{
    /// Core4 engine facade
    class EngineFacade : 
        public IInputListener,
        public Singleton<EngineFacade>
    {
    public:
        /// Ctor.
        EngineFacade();

        /// Initialize Core4 engine.
        /// @param renderSystem Render system to use.
        void init(IRenderSystem * renderSystem);
 
        /// Update everything and render.
        /// @param dt Time since last update, in ms.
        void updateAndRender(float dt);

        /// Cleanup Core4 engine.
        void cleanup();

        /// @see IInputListener
        void onKeyDown(const Buttons::Type & button);

        /// @see IInputListener
        void onKeyUp(const Buttons::Type & button);

        /// @see IInputListener
        void onMouseMove(const Vector2 & mousePos);
    private:
        IRenderSystem *  m_renderSystem;
        LocationMap      m_testMap;
        LocationRenderer m_mapRenderer;
        Vector2          m_mousePos;
        MouseMap         m_mouseMap;
    };
} // namespace Core4