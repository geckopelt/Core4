#pragma once

#include "Serialization/TypeConverters.hxx"

class TypeConverterTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TypeConverterTests);
        CPPUNIT_TEST(boolConversionTest);
        CPPUNIT_TEST(intConversionTest);
        CPPUNIT_TEST(sizetConversionTest);
        CPPUNIT_TEST(floatConversionTest);
        CPPUNIT_TEST(stringConversionTest);
        CPPUNIT_TEST(colorConversionTest);
        CPPUNIT_TEST(vector2ConversionTest);
        CPPUNIT_TEST(pointConversionTest);
        CPPUNIT_TEST(vectorConversionTest);
    CPPUNIT_TEST_SUITE_END();

    template <typename T> std::string toString(T value)
    {
        std::string str;
        TypeConverters::toString(value, str);
        return str;
    }

    template <typename T> T fromString(const std::string & str)
    {
        T value;
        TypeConverters::fromString(str, value);
        return value;
    }

    template <typename T> T twoWay(const T & value)
    {
        return fromString<T>(toString<T>(value));
    }

public:
    void boolConversionTest()
    {
        CPPUNIT_ASSERT(twoWay<bool>(true) == true);
        CPPUNIT_ASSERT(twoWay<bool>(false) == false);
    }

    void intConversionTest()
    {
        CPPUNIT_ASSERT(twoWay<int>(42) == 42);
    }

    void sizetConversionTest()
    {
        CPPUNIT_ASSERT(twoWay<size_t>(42) == 42);
    }

    void floatConversionTest()
    {
        const float Pi = 3.14f;
        CPPUNIT_ASSERT(twoWay<float>(Pi) == Pi);
    }

    void stringConversionTest()
    {
        CPPUNIT_ASSERT(twoWay<std::string>("foo") == "foo");
    }

    void colorConversionTest()
    {
        const Color test(255, 128, 64, 92);
        CPPUNIT_ASSERT(twoWay<Color>(test) == test);
    }

    void vector2ConversionTest()
    {
        const Vector2 test(4.0f, 256.0f);
        CPPUNIT_ASSERT(twoWay<Vector2>(test) == test);
    }

    void pointConversionTest()
    {
        const Point test(42, 31337);
        CPPUNIT_ASSERT(twoWay<Point>(test) == test);
    }

    void vectorConversionTest()
    {
        typedef std::vector<size_t> SizetVector;
        SizetVector test;
        test.push_back(42);
        test.push_back(31337);
        test.push_back(0);
        test.push_back(100500);
        CPPUNIT_ASSERT(twoWay<SizetVector>(test) == test);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TypeConverterTests);