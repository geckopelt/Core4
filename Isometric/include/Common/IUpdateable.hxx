#pragma once

/// @file IUpdateable.hxx
/// @brief Updateable objects interface

namespace Core4
{
    /// An updateable interface.
    struct Updateable
    {
        /// Update something.
        /// @param dt Update interval, in ms.
        virtual void update(float dt) = 0;

        virtual ~Updateable() {}
    };
} // namespace Core4
