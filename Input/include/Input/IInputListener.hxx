#pragma once

#include "Types/Vector2.hxx"
#include "Input/Buttons.hxx"

/// @file IInputListener.hxx
/// @brief An input listener interface.

namespace Core4
{
    /// An input listener interface.
    struct IInputListener
    {
        /// Called on button pressed.
        /// @param button Button
        virtual void onKeyDown(const Buttons::Type & button) = 0;

        /// Called on button released.
        /// @param button Button
        virtual void onKeyUp(const Buttons::Type & button) = 0;

        /// Called on mouse movement.
        /// @param mousePos Mouse position, in pixels.
        virtual void onMouseMove(const Vector2 & mousePos) = 0;

        virtual ~IInputListener() {}
    };
} // namespace Core4

