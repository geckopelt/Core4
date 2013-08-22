#pragma once

/// @file IsoDirection.hxx
/// @brief An isometric direction.

namespace Core4
{
    /// A 8-way isometric direction enum.
    enum IsoDirection
    {
        North = 0,
        NorthEast = 1,
        East = 2,
        SouthEast = 3,
        South = 4,
        SouthWest = 5,
        West = 6,
        NorthWest = 7,
        UnknownDirection = 0xFFFFFFFF
    };
} // namespace Core4

