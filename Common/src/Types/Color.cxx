#include "Types/Color.hxx"

namespace Core4
{
    const Color Color::Red       = Color(255, 0, 0, 255);
    const Color Color::Green     = Color(0, 255, 0, 255);
    const Color Color::Blue      = Color(0, 0, 255, 255);
    const Color Color::White     = Color(255, 255, 255, 255);
    const Color Color::Black     = Color(0, 0, 0, 255);
    const Color Color::DarkGray  = Color(150, 150, 150, 255);
    const Color Color::LightGray = Color(200, 200, 200, 255);
    const Color Color::Yellow    = Color(255, 255, 0, 255);

    //----------------------------------------------------------------------------------------------------------
    Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) :
	      m_red(r), m_green(g), m_blue(b), m_alpha(a) {}

    //----------------------------------------------------------------------------------------------------------
    Color::Color() : m_red(255), m_green(255), m_blue(255), m_alpha(255) {}

    //----------------------------------------------------------------------------------------------------------
    bool Color::operator == (const Color & other) const
    {
        return 
            (m_red == other.m_red) &&
            (m_green == other.m_green) &&
            (m_blue  == other.m_blue) &&
            (m_alpha == other.m_alpha);
    }

    //----------------------------------------------------------------------------------------------------------
    unsigned char Color::red() const
    {
        return m_red;
    }

    //----------------------------------------------------------------------------------------------------------
    unsigned char Color::green() const
    {
        return m_green;
    }

    //----------------------------------------------------------------------------------------------------------
    unsigned char Color::blue() const
    {
        return m_blue;
    }

    //----------------------------------------------------------------------------------------------------------
    unsigned char Color::alpha() const
    {
        return m_alpha;
    }

    //----------------------------------------------------------------------------------------------------------
    void Color::setRed(unsigned char r)
    {
        m_red = r;
    }

    //----------------------------------------------------------------------------------------------------------
    void Color::setGreen(unsigned char g)
    {
        m_green = g;
    }
    
    //----------------------------------------------------------------------------------------------------------
    void Color::setBlue(unsigned char b)
    {
        m_blue = b;
    }
    
    //----------------------------------------------------------------------------------------------------------
    void Color::setAlpha(unsigned char a)
    {
        m_alpha = a;
    }
}