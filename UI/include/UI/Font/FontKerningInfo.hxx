#ifndef CORE4_FONTKERNINGINFO_H
#define CORE4_FONTKERNINGINFO_H

/// @file FontKerningInfo.hxx
/// @brief Font kerning info

#include <map>

namespace Core4
{
    /// Font kerning info
    class FontKerningInfo
    {
        /// Add kerning info.
        /// @param left Left character
        /// @param right Right character
        /// @param amount Kerning, in pixel
        void addKerningInfo(wchar_t left, wchar_t right, float amount);

        /// Get kernings count.
        /// @return Kernings count.
        size_t getKerningsCount() const;

        /// Get kerning.
        /// @param left Left character
        /// @param right Right character
        float getKerning(wchar_t left, wchar_t right) const;
    private:
        typedef std::map<wchar_t, float> CharacterKernings;
        typedef std::map<wchar_t, CharacterKernings > Kernings;
        Kernings m_kernings;
    };
} // namespace Core4

#endif // CORE4_FONTKERNINGINFO_H