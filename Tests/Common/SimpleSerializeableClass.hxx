#pragma once

#include "Serialization/Serializeable.hxx"

class Foo : public Serializeable
{
public:
    Foo(int foo, const std::string & bar, const Vector2 & titi, const Point & toto) :
        m_foo(foo), m_bar(bar), m_titi(titi), m_toto(toto)
    {
    }

    Foo() : m_foo(0) {}

    void perform(TiXmlElement & element, const SerializeActionType action)
    {
        C4_SERIALIZE_ATTR(m_foo);
        C4_SERIALIZE_ATTR(m_bar);
        C4_SERIALIZE_ATTR(m_titi);
        C4_SERIALIZE_ATTR(m_toto);
     }

    bool operator == (const Foo & other)
    {
        return 
            m_foo == other.m_foo && 
            m_bar == other.m_bar && 
            m_titi == other.m_titi && 
            m_toto == other.m_toto;
    }

private:
    int m_foo;
    std::string m_bar;
    Vector2 m_titi;
    Point m_toto;
};
