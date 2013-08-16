#pragma once

/// @file IEffect.hxx
/// @brief Image processing effect interface.

#include "Image/ImageManipulator.hxx"

namespace Core4
{
    /// Image processing effect interface.
    struct IEffect
    {
        virtual void applyEffect(ImageManipulator & im) = 0;
        virtual ~IEffect() {}
    };
} // namespace Core4