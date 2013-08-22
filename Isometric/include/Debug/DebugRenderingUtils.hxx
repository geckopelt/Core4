#pragma once

/// @file DebugRenderingUtils.hxx
/// @brief Simple debug rendering utilities

#include "Types/Vector2.hxx"
#include "Types/Color.hxx"
#include "Render/Primitive.hxx"

namespace Core4
{
    /// Simple debug rendering utilities.
    struct DebugRenderingUtils
    {
        /// Add tile borders to a primitive.
        /// @param screenPos Screen position, in pixels.
        /// @param color Color.
        /// @param primitive Primitive to fill.
        static void addTileBordersPrimitive(const Vector2 & screenPos, const Color & color, Primitive & dest);
    };
} // namespace Core4
