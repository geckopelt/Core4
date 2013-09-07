#ifndef CORE4_FONTINFO_H
#define CORE4_FONTINFO_H

/// @file FontInfo.hxx
/// @brief Font info container class.

#include <string>
#include <Serialization/Serializeable.hxx>
#include <Types/Vector2.hxx>

namespace Core4
{
    /// Font info container.
    class FontInfo
    {
    public:
        /// Ctor.
        FontInfo();

        void setFace(const std::string & face);

        const std::string & getFace() const;

        void setSize(const size_t size);

        const size_t getSize() const;

        void setSpacing(const Vector2 & spacing);

        const Vector2 & getSpacing() const;
    private:
        std::string m_face;
        size_t      m_size;
        Vector2     m_spacing;
    };
} // namespace Core4

#endif // CORE4_FONTINFO_H