#pragma once

class StringUtilsTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(StringUtilsTests);
        CPPUNIT_TEST(intToStringTest);
        CPPUNIT_TEST(floatToStringTest);
        CPPUNIT_TEST(caseTest);
        CPPUNIT_TEST(splitStringTest);
    CPPUNIT_TEST_SUITE_END();

public:
    void intToStringTest()
    {
        CPPUNIT_ASSERT("42" == StringUtils::intToString(42));   
    }

    void floatToStringTest()
    {
        CPPUNIT_ASSERT(StringUtils::floatToString(3.14f).find_first_of("3.14") == 0);  
    }

    void caseTest()
    {
        CPPUNIT_ASSERT("foo" == StringUtils::toLower("Foo"));
        CPPUNIT_ASSERT("FOO" == StringUtils::toUpper("Foo"));
    }

    void splitStringTest()
    {
        {
            std::vector<std::string> out;
            StringUtils::splitString("hello", " ", out);
            CPPUNIT_ASSERT(1 == out.size());
            CPPUNIT_ASSERT("hello" == out.at(0));
        }

        {
            std::vector<std::string> out;
            StringUtils::splitString("foo; bar; test", "; ", out);
            CPPUNIT_ASSERT(3 == out.size());
            CPPUNIT_ASSERT("foo" == out.at(0));
            CPPUNIT_ASSERT("bar" == out.at(1));
            CPPUNIT_ASSERT("test" == out.at(2));
        }
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(StringUtilsTests);