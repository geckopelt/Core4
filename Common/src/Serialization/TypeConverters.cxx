#pragma once

#include "Utils/Guards.hxx"
#include "Utils/StringUtils.hxx"
#include "Types/Color.hxx"
#include "Serialization/TypeConverters.hxx"

namespace Core4
{ 
    const std::string Separator = ",";

    namespace
    {
        std::vector<std::string> split(const std::string & in, size_t partCountExpected, const std::string & errorMessage)
        {
            std::vector<std::string> components;
            StringUtils::splitString(in, Separator, components);
            CORE4_CHECK(partCountExpected == components.size(), errorMessage);
            return components;
        }
    }

    // bool
    void TypeConverters::toString(bool in, std::string & out)           { out = in ? "yes" : "no"; }
    void TypeConverters::fromString(const std::string & in, bool & out) { out = (in == "yes"); }

    // int
    void TypeConverters::toString(int in, std::string & out)           { out = StringUtils::intToString(in); }
    void TypeConverters::fromString(const std::string & in, int & out) { out = atoi(in.c_str()); }

    // size_t
    void TypeConverters::toString(size_t in, std::string & out)           { out = StringUtils::intToString(in); }
    void TypeConverters::fromString(const std::string & in, size_t & out) { out = atoi(in.c_str()); }

    // float
    void TypeConverters::toString(const float & in, std::string & out)   { out = StringUtils::floatToString(in); }
    void TypeConverters::fromString(const std::string & in, float & out) { out = (float)atof(in.c_str()); }

    // std::string
    void TypeConverters::toString(const std::string & in, std::string & out)   { out = in; }
    void TypeConverters::fromString(const std::string & in, std::string & out) { out = in; }

    // Color
    void TypeConverters::toString(const Color & in, std::string & out)
    {
        out = StringUtils::intToString(in.red()) + Separator + 
            StringUtils::intToString(in.green()) + Separator + 
            StringUtils::intToString(in.blue()) + Separator + 
            StringUtils::intToString(in.alpha());
    }

    void TypeConverters::fromString(const std::string & in, Color & out)
    {
        std::vector<std::string> components = split(in, 4, "Invalid color string");
        out.setRed(atoi(components.at(0).c_str()));
        out.setGreen(atoi(components.at(1).c_str()));
        out.setBlue(atoi(components.at(2).c_str()));
        out.setAlpha(atoi(components.at(3).c_str()));
    }

    // Vector2
    void TypeConverters::toString(const Vector2 & in, std::string & out)
    {
        out = StringUtils::floatToString(in.x()) + Separator + StringUtils::floatToString(in.y());
    }

    void TypeConverters::fromString(const std::string & in, Vector2 & out)
    {
        std::vector<std::string> components = split(in, 2, "Invalid Vector2 string");
        out.setX((float)atof(components.at(0).c_str()));
        out.setY((float)atof(components.at(1).c_str()));
    }

    // Point
    void TypeConverters::toString(const Point & in, std::string & out)
    {
        out = StringUtils::intToString(in.x()) + Separator + StringUtils::intToString(in.y());
    }

    void TypeConverters::fromString(const std::string & in, Point & out)
    {
        std::vector<std::string> components = split(in, 2, "Invalid Point string");
        out.setX(atoi(components.at(0).c_str()));
        out.setY(atoi(components.at(1).c_str()));
    }

    // std::vector<size_t>
    void TypeConverters::toString(const std::vector<size_t> & in, std::string & out)
    {
        for (size_t index = 0; index < in.size(); index++)
        {
            out += StringUtils::intToString(in.at(index));
            if (index < in.size() - 1)
                out += Separator;
        }
    }

    void TypeConverters::fromString(const std::string & in, std::vector<size_t> & out)
    {
        std::vector<std::string> components;
        StringUtils::splitString(in, Separator, components);
        out.resize(components.size());
        for (size_t index = 0; index < components.size(); index++)
        {
            out[index] = atoi(components.at(index).c_str());
        }
    }
} // namespace Core4
