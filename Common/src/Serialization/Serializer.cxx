#include "Serialization/XmlDocument.hxx"
#include "Serialization/Serializer.hxx"

namespace Core4
{
    const TiXmlDeclaration Declaration("1.0", "", "");

    //------------------------------------------------------------------------------------------------------------------------------
    std::string Serializer::serialize(Serializeable * src, const std::string & nodeName)
    {
        XmlDocument xml;
        xml.InsertEndChild(Declaration);
        TiXmlElement * rootElement = static_cast<TiXmlElement*>(xml.InsertEndChild(TiXmlElement(nodeName.c_str())));
        src->perform(*rootElement, Serialize);
        return xml.toString();
    }

    //------------------------------------------------------------------------------------------------------------------------------ 
    void Serializer::deserialize(const std::string & xml, const std::string & nodeName, Serializeable * dest)
    {
        XmlDocument xmlDocument;
        xmlDocument.Parse(xml.c_str(), 0, TIXML_DEFAULT_ENCODING); 

        CORE4_CHECK(NULL != dest, "Object to be deserialized into is NULL");
        TiXmlElement * rootElement = xmlDocument.FirstChildElement(nodeName.c_str());
        CORE4_CHECK(NULL != rootElement, "No root element named \"" + nodeName + "\" found");
        dest->perform(*rootElement, Deserialize);
    }
} // namespace Core4
