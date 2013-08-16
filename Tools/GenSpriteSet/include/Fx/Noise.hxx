#pragma once

/// @file Noise.hxx
/// @brief Noise effect.

#include "Types/Color.hxx"
#include "Fx/IEffect.hxx"

namespace Core4
{
    /// A simple noise effect.
    class Noise : public IEffect
    {
    public:
        /// @param baseColor Base color of a noise.
        /// @param n Noise fluctuation parameter
        Noise(const Color & baseColor, unsigned char noise);

        /// @see IEffect
        void applyEffect(ImageManipulator & im);
    private:
        Color m_baseColor;
        unsigned char m_noise;
    };

} // namespace Core4