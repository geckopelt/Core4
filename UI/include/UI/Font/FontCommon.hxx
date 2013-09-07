#ifndef CORE4_FONTCOMMON_H
#define CORE4_FONTCOMMON_H

/// @file FontCommon.hxx
/// @brief Font common info container class.

#include <string>
#include <Serialization/Serializeable.hxx>
#include <Types/Vector2.hxx>

namespace Core4
{
    /// Font common info container.
    class FontCommon
    {
    public:
        /// Ctor.
        FontCommon();

        /// Set font line height.
        /// @param lineHeight Font line height, in pixels.
        void setLineHeight(float lineHeight);

        /// Get font line height.
        /// @return Font line height, in pixels.
        float getLineHeight() const;
    private:
        float m_lineHeight;
    };
} // namespace Core4

#endif