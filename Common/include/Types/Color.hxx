#pragma once

/// @file Color.hxx
/// @brief RGBA color class

namespace Core4
{

/// A simple RGBA color class
class Color
{
    unsigned char m_red;
    unsigned char m_green;
    unsigned char m_blue;
    unsigned char m_alpha;
public:
    static const Color Red;       //< Common color: red.
    static const Color Green;     //< Common color: green.
    static const Color Blue;      //< Common color: blue.
    static const Color White;     //< Common color: white.
    static const Color Black;     //< Common color: black
    static const Color LightGray; //< Common color: light gray
    static const Color DarkGray;  //< Common color: dark gray
    static const Color Yellow;    //< Common color: yellow

    /// Ctor.
    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

    /// Default ctor. Initializes Color into white.
    Color();

    /// Compares two Colors.
    bool operator == (const Color & other) const;

    /// Get red component of a color.
    unsigned char red() const;

    /// Get green component of a color.
    unsigned char green() const;

    /// Get blue component of a color.
    unsigned char blue() const;

    /// Get alpha component of a color.
    unsigned char alpha() const;

    /// Set red component of a color.
    void setRed(unsigned char r);

    /// Set green component of a color.
    void setGreen(unsigned char g);
    
    /// Set blue component of a color.
    void setBlue(unsigned char b);
    
    /// Set alpha component of a color.
    void setAlpha(unsigned char a);
};

} // namespace Core4
