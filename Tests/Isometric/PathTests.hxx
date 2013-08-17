#pragma once

#include "Serialization/Serializer.hxx"
#include "Pathfinding/Path.hxx"

class PathTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(PathTests);
        CPPUNIT_TEST(pathSerializationTest);
    CPPUNIT_TEST_SUITE_END();

    // A simple smoke test.
    void pathSerializationTest()
    {
        Path path1;
        path1.push_back(North);
        path1.push_back(North);
        path1.push_back(East);
        path1.push_back(SouthWest);

        const std::string NodeName("pathTest");
        const std::string xml = Serializer::serialize(&path1, NodeName);

        Path path2;
        Serializer::deserialize(xml, NodeName, &path2);
        CPPUNIT_ASSERT(path1 == path2);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(PathTests);

