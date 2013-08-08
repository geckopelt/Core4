#pragma once

#include "Serialization/Serializer.hxx"
#include "SimpleSerializeableClass.hxx"
#include "ComplexSerializeableClass.hxx"

class SerializationTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(SerializationTests);
        CPPUNIT_TEST(simpleSerializationTest);
        CPPUNIT_TEST(complexSerializationTest);
    CPPUNIT_TEST_SUITE_END();

    void simpleSerializationTest()
    {
        const std::string NodeName("Foo");

        Foo foo(42, "ololo", Vector2(128.0f, 256.0f), Point(32, 16));
        std::string xml = Serializer::serialize(static_cast<Core4::Serializeable*>(&foo), NodeName);

        Foo bar;
        Serializer::deserialize(xml, NodeName, &bar);

        CPPUNIT_ASSERT(foo == bar);
    }

    void complexSerializationTest()
    {
        const std::string NodeName("Complex");

        ComplexFoo cfoo(Foo(42, "ololo", Vector2(128.0f, 256.0f), Point(32, 16)), 8, "Smile");
        std::string xml = Serializer::serialize(static_cast<Core4::Serializeable*>(&cfoo), NodeName);

        ComplexFoo cbar;
        Serializer::deserialize(xml, NodeName, &cbar);

        CPPUNIT_ASSERT(cfoo == cbar);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(SerializationTests);