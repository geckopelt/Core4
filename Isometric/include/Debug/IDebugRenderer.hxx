#pragma once

/// @file IDebugRenderer.hxx
/// @brief Debug renderer interface

#include "Types/Vector2.hxx"
#include "Location/BoundingBox.hxx"
#include "Location/LocationMapObject.hxx"
#include "Location/LocationMapCell.hxx"

namespace Core4
{
    /// Debug renderer interface.
    struct IDebugRenderer
    {
        /// Called each frame
        virtual void onNewFrame() = 0;

        /// Called on each tile rendered.
        /// @param screenPos Screen position, in pixels.
        /// @param cell A corresponding map cell.
        virtual void onTileRendered(const Vector2 & screenPos, const LocationMapCell & cell) = 0;

        /// Called on each object rendered.
        /// @param boundingBox Object's bounding box at screen, in pixels.
        /// @param object Object reference.
        virtual void onObjectRendered(const BoundingBox & boundingBox, const LocationMapObject & object) = 0;

        /// Called on each render.
        /// @param renderSystem Render system
        virtual void onRender(IRenderSystem * renderSystem) = 0;

        virtual ~IDebugRenderer() {}
    };
} // namespace Core4
