#include "Serialization/SerializationUtils.hxx"
#include "Light/Light.hxx"

namespace Core4
{
    //--------------------------------------------------------------------------------------------------
    Light::Light() : m_red(0), m_green(0), m_blue(0), m_fog(0), m_enabled(false), m_range(0)
    {
    }

    //--------------------------------------------------------------------------------------------------
    void Light::setComponents(int red, int green, int blue, int fog)
    {
        m_red   = red;
        m_green = green;
        m_blue  = blue;
        m_fog   = fog;
    }

    //--------------------------------------------------------------------------------------------------
    int Light::red() const
    {
        return m_red;
    }

    //--------------------------------------------------------------------------------------------------
    int Light::green() const
    {
        return m_green;
    }

    //--------------------------------------------------------------------------------------------------
    int Light::blue() const
    {
        return m_blue;
    }

    //--------------------------------------------------------------------------------------------------
    int Light::fog() const
    {
        return m_fog;
    }

    //--------------------------------------------------------------------------------------------------
    void Light::setMapPos(const Vector2 & pos)
    {
        m_mapPos = pos;
    }

    //--------------------------------------------------------------------------------------------------
    const Vector2 & Light::getMapPos() const
    {
        return m_mapPos;
    }

    //--------------------------------------------------------------------------------------------------
    void Light::enable(bool enable)
    {
        m_enabled = enable;
    }

    //--------------------------------------------------------------------------------------------------
    bool Light::isEnabled() const
    {
        return m_enabled;
    }

    //--------------------------------------------------------------------------------------------------
    void Light::setRange(int range)
    {
        m_range = range;
    }

    //--------------------------------------------------------------------------------------------------
    int Light::getRange() const
    {
        return m_range;
    }

    //--------------------------------------------------------------------------------------------------
    void Light::perform(TiXmlElement & element, const SerializeActionType action)
    {
        C4_SERIALIZE_ATTR(m_red);
        C4_SERIALIZE_ATTR(m_green);
        C4_SERIALIZE_ATTR(m_blue);
        C4_SERIALIZE_ATTR(m_fog);
        C4_SERIALIZE_ATTR(m_enabled);
        C4_SERIALIZE_ATTR(m_range);
        C4_SERIALIZE_CHILD(m_mapPos, "m_mapPos");
    }
} // namespace C4
