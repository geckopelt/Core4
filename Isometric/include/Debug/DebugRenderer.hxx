#pragma once

/// @file DebugRenderer.hxx
/// @brief Debug renderer implementation

#include "Debug/IDebugRenderer.hxx"
#include "Render/Primitive.hxx"
#include "Render/IRenderSystem.hxx"

namespace Core4
{
    /// Debug renderer implementation.
    class DebugRenderer : public IDebugRenderer
    {
    public:
        /// @see IDebugRenderer
        void onNewFrame();

        /// @see IDebugRenderer
        void onTileRendered(const Vector2 & screenPos, const LocationMapCell & cell);

        /// @see IDebugRenderer
        void onObjectRendered(const BoundingBox & boundingBox, const LocationMapObject & object);

        /// @see IDebugRenderer
        void onRender(IRenderSystem * renderSystem);
    private:
        Primitive m_tiles;
        Primitive m_objects;
    };
} // namespace Core4
