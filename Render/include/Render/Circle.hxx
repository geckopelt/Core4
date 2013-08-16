#pragma once

/// @file Circle.hxx
/// @brief A circle primitive.

#include "Primitive.hxx"

namespace Core4
{
    /// A circle primitive class
    class Circle : public Primitive
    {
    public:
        Circle(float x, float y, float radius, const Color & color);
    private:
        Circle();
    };
}