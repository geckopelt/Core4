#ifndef CORE4_FONTCHAR_H
#define CORE4_FONTCHAR_H

/// @file FontChar.hxx
/// @brief Font character info.

#include "Types/Rect.hxx"
#include "Types/Vector2.hxx"

namespace Core4
{
    // Font character info.
    class FontChar
    {
    public:
        /// Ctor.
        FontChar();

        /// Set character value
        /// @param c Unicode character value
        void setChar(wchar_t c);

        /// Get character value
        /// @return Unicode character value
        wchar_t getChar() const;

        /// Set character size and position.
        /// @param Size and position, in pixels.
        void setRect(const Rect & rect);

        /// Get character size and position.
        /// @return Size and position, in pixels.
        const Rect & getRect() const;

        /// Set horizontal advance value.
        /// @param X Advance value, in position.
        void setAdvanceX(float advanceX);

        /// Get horizontal advance value.
        /// @return Advance value, in position.
        float getAdvanceX() const;

        /// Set page number.
        /// @param pageNumber Page number.
        void setPageNumber(size_t pageNumber);

        /// Get page number.
        /// @return Page number.
        size_t getPageNumber() const;
    private:
        wchar_t m_char;
        Rect    m_rect;
        Vector2 m_offset;
        float   m_advanceX;
        size_t  m_pageNumber;
    };
} // namespace Core4

#endif
