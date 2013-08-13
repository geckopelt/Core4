#pragma once

#include "Serialization/Serializer.hxx"
#include "Sprites/ISpriteManager.hxx"
#include "Sprites/SpriteDescriptionsLoader.hxx"

class SpriteManagerTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(SpriteManagerTests);
        CPPUNIT_TEST(foo);
    CPPUNIT_TEST_SUITE_END();

    void foo()
    {
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(SpriteManagerTests);

