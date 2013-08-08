#pragma once

#include "Serialization/SerializeableVector.hxx"
#include "Serialization/SerializeableList.hxx"
#include "SimpleSerializeableClass.hxx"

class ComplexFoo : public Core4::Serializeable
{
public:
    ComplexFoo(const Foo & foo, int count, const std::string & name) : 
      m_foo(foo), m_count(count), m_name(name) 
    {
        m_fooVector.push_back(Foo(2, "foo", Vector2(), Point(3, 4)));
        m_fooList.push_back(m_fooVector);
        m_fooVector.push_back(Foo(1, "foo1", Vector2(0.5f, 0.1f), Point(3, 4)));
        m_fooVector.push_back(Foo(7, "foo7", Vector2(0.15f, 0.11f), Point(31, 41)));
        m_fooList.push_back(m_fooVector);
    }

    ComplexFoo() : m_count(0) {}

    void perform(TiXmlElement & element, const SerializeActionType action)
    {
        C4_SERIALIZE_ATTR(m_count);
        C4_SERIALIZE_ATTR(m_name);
        C4_SERIALIZE_CHILD(m_foo, "foo");
        C4_SERIALIZE_CHILD(m_fooVector, "foos");
        C4_SERIALIZE_CHILD(m_fooList, "bars");
    }

    bool operator == (const ComplexFoo & other)
    {
        return m_foo == other.m_foo && m_count == other.m_count && m_name == other.m_name;
    }

private:
    Foo m_foo;
    int m_count;
    std::string m_name;
    SerializeableVector<Foo> m_fooVector;
    SerializeableList<SerializeableVector<Foo>> m_fooList;
};
