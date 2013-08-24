#pragma once

/// @file MouseMap.hxx
/// @brief Mousemap implementation.

#include <vector>
#include "Location/IsoDirection.hxx"
#include "Location/LocationRenderer.hxx"
#include "Types/Vector2.hxx"
#include "Types/Point.hxx"

namespace Core4
{
    /// Mousemap implementation.
    /// Mousemap is used to convert screen/pixel coords into isometric cell coords.
    class MouseMap
    {
    public:
        /// Ctor.
        MouseMap();

        /// Convert screen coords into map cell coords.
        /// @param screen Screen position, in pixels.
        /// @param scrollPos World scroll position, in pixels.
        /// @return Cell position.
        const Point screenToTile(const Vector2 & screen, const Vector2 & scrollPos) const;
    private:
        std::vector<IsoDirection> m_mouseMap;
    };
} // namespace Core4