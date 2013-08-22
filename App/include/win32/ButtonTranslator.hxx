#pragma once

/// @file ButtonTranslator.hxx
/// @brief Windows Virtual Key translator

#include "Input/Buttons.hxx"

namespace Core4
{
    /// Windows virtual key to button translator
    struct ButtonTranslator
    {
        /// Convert Virtual Key into a button.
        /// @param virtualKey Windows Virtual Key
        /// @return Button.
        static Buttons::Type translateButton(int virtualKey);
    };
} // namespace Core4
