#include "UI/Font/FontChar.hxx"

namespace Core4
{
    //--------------------------------------------------------------------------------------------
    FontChar::FontChar() : m_char(0), m_advanceX(0.f), m_pageNumber(0)
    {
    }

    //--------------------------------------------------------------------------------------------
    void FontChar::setChar(wchar_t c)
    {
        m_char = c;
    }

    //--------------------------------------------------------------------------------------------
    wchar_t FontChar::getChar() const
    {
        return m_char;
    }

    //--------------------------------------------------------------------------------------------
    void FontChar::setRect(const Rect & rect)
    {
        m_rect = rect;
    }

    //--------------------------------------------------------------------------------------------
    const Rect & FontChar::getRect() const
    {
        return m_rect;
    }

    //--------------------------------------------------------------------------------------------
    void FontChar::setAdvanceX(float advanceX)
    {
        m_advanceX = advanceX;
    }

    //--------------------------------------------------------------------------------------------
    float FontChar::getAdvanceX() const
    {
        return m_advanceX;
    }

    //--------------------------------------------------------------------------------------------
    void FontChar::setPageNumber(size_t pageNumber)
    {
        m_pageNumber = pageNumber;
    }

    //--------------------------------------------------------------------------------------------
    size_t FontChar::getPageNumber() const
    {
        return m_pageNumber;
    }
} // namespace Core4
