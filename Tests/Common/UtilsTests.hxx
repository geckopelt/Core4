#pragma once

#include "Utils/Crc32.hxx"

class UtilsTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(UtilsTests);
        CPPUNIT_TEST(crc32Test);
    CPPUNIT_TEST_SUITE_END();

    void crc32Test()
    {
        CPPUNIT_ASSERT(0 == Crc32::calculate(""));
        CPPUNIT_ASSERT(0xCBF43926 == Crc32::calculate("123456789"));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(UtilsTests);