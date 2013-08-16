#pragma once

/// @file ILocationMovementListener.hxx
/// @brief Location object movement callback listener.

#include "Location/LocationMapObject.hxx"

namespace Core4
{
    /// An interface that provides movement-related callback method.
    struct ILocationObjectMovementListener
    {
        /// Called when location object finshes its movement.
        /// @param object Location object reference.
        void onMovementFinished(LocationMapObject & object);

        virtual ~ILocationMovementListener() {}
    };
} // namespace Core4