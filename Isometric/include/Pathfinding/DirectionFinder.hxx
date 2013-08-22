#pragma once

/// @file DirectionFinder.hxx
/// @brief A simple neighbour cell direction finder.

#include "Types/Point.hxx"
#include "Location/IsoDirection.hxx"

namespace Core4
{
    /// A simple neighbour cell direction finder.
    struct DirectionFinder
    {
        /// Determine direction from "fromCell" to "toCell".
        /// @param fromCell Source map cell.
        /// @param toCell Dest map cell.
        /// @return Isometric direction
        static IsoDirection getDirection(const Point & fromCell, const Point & toCell);
    };
} // namespace Core4


/// Получить направление между точками
  /// @param from Точка, откуда смотрят
  /// @param to Точка, куда смотрят
  /// @return Направление от точки a к точке b
  int 