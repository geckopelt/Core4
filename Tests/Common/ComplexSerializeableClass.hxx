#pragma once

// TODO: add serializeable vectors, maps, lists etc.

#include "SimpleSerializeableClass.hxx"

class ComplexFoo : public Core4::Serializeable
{
public:
    // TODO

private:
    Foo m_foo;
    int m_count;
    std::string m_name;
};
