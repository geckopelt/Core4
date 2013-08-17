#pragma once

/// @file ILocationMovementListener.hxx
/// @brief Location object movement callback listener.

#include "Location/LocationMapObject.hxx"

namespace Core4
{
    class LocationMapObject;

    /// An interface that provides movement-related callback method.
    struct ILocationObjectMovementListener
    {
        /// Called when location object finshes its movement.
        /// @param object Location object reference.
        virtual void onMovementFinished(LocationMapObject * object) = 0;

        virtual ~ILocationObjectMovementListener() {}
    };
} // namespace Core4