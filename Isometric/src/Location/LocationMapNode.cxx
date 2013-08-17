#include "Location/LocationMapNode.hxx"

namespace Core4
{
    //----------------------------------------------------------------------------------------------------------
    LocationMapNode::LocationMapNode() : m_height(0)
    {
    }

    //----------------------------------------------------------------------------------------------------------
    void LocationMapNode::setHeight(float height)
    {
        m_height = height;
    }

    //----------------------------------------------------------------------------------------------------------
    float LocationMapNode::getHeight() const
    {
        return m_height;
    }

    //----------------------------------------------------------------------------------------------------------
    void LocationMapNode::setColor(const Color & color)
    {
        m_color = color;
    }

    //----------------------------------------------------------------------------------------------------------
    const Color & LocationMapNode::getColor() const
    {
        return m_color;
    }

    //----------------------------------------------------------------------------------------------------------
    void LocationMapNode::perform(TiXmlElement & element, const SerializeActionType action)
    {
        C4_SERIALIZE_ATTR(m_height);
        C4_SERIALIZE_ATTR(m_color);
    }
} // namespace Core4
