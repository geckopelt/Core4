#pragma once

/// @file TileBasics.hxx
/// @brief Isometric tile utils and stuff.

// TODO: Once again, an include directive quickfix.
#include "Serialization/Serializeable.hxx" 

#include "Types/Point.hxx"
#include "Types/Vector2.hxx"
#include "Location/IsoDirection.hxx"

namespace Core4
{
    /// Basic isometric tiles stuff.
    struct TileBasics
    {
        static const float TileWidth;       //< Core4 engine cell width, in pixels (64). Can't see any reason to make it configurable right now.
        static const float TileHeight;      //< Core4 engine cell height, in pixels (32). Can't see any reason to make it configurable right now.
        static const float TileAspectRatio; //< Isometric tile dimensions aspect ratio.

        /// Get neighbour cell position.
        /// @param from Source cell position.
        /// @param direction Direction of a neighbour.
        /// @return Neighbour cell position.
        static const Point getNeighbourCell(const Point & from, IsoDirection direction);

        /// Get tiles' screen position.
        /// @param tile Cell position.
        /// @return Screen position, in pixels.
        static const Vector2 getTileScreenPos(const Point & tile);
    };
} // namespace Core4