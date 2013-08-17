#include <string>
#include <map>
#include <TinyXML.h>
#include "Utils/Guards.hxx"
#include "Utils/Singleton.hxx"
#include "Utils/StringUtils.hxx"
#include "Pathfinding/Path.hxx"

namespace Core4
{
    namespace
    {
        const std::string Separator = ";";
        
        class IsoDirectionConverter : public Singleton<IsoDirectionConverter>
        {
        public:
            IsoDirectionConverter()
            {
                addMapping(North, "N");
                addMapping(NorthEast, "NE");
                addMapping(East, "E");
                addMapping(SouthEast, "SE");
                addMapping(South, "S");
                addMapping(SouthWest, "SW");
                addMapping(West, "W");
                addMapping(NorthWest, "NW");
                addMapping(UnknownDirection, "?");
            }

            void addMapping(IsoDirection direction, const std::string & name)
            {
                m_to[direction] = name;
                m_from[name] = direction;
            }

            const std::string & toString(IsoDirection direction) const
            {
                std::map<IsoDirection, std::string>::const_iterator it = m_to.find(direction);
                CORE4_CHECK(it != m_to.end(), "Direction is unmapped");
                return it->second;
            }

            const IsoDirection & fromString(const std::string & str) const
            {
                std::map<std::string, IsoDirection>::const_iterator it = m_from.find(str);
                CORE4_CHECK(it != m_from.end(), "Unknown direction: " + str);
                return it->second;
            }
        private:
            std::map<IsoDirection, std::string> m_to;
            std::map<std::string, IsoDirection> m_from;
        };
    }

    //--------------------------------------------------------------------------------------------------------
    void Path::perform(TiXmlElement & element, const SerializeActionType action)
    {
        const std::string tagName("path");
        const std::string attrName("directions");

        TiXmlElement * child =
            (action == Serialize) ?
            static_cast<TiXmlElement*>(element.InsertEndChild(TiXmlElement(tagName.c_str()))) :
            element.FirstChildElement(tagName.c_str());

        if (action == Serialize)
        {
            child->SetAttribute(attrName.c_str(), toString().c_str());
        }
        else
        {
            CORE4_CHECK(NULL != child, "Child element is NULL");
            const char * destinations = child->Attribute(attrName.c_str());
            CORE4_CHECK(NULL != child, "Path has no destinations");
            fromString(destinations);
        }
    }

    //--------------------------------------------------------------------------------------------------------
    const std::string Path::toString() const
    {
        std::string res;
        for (const_iterator it = begin(); it != end(); it++)
        {
            res += (IsoDirectionConverter::getSingleton().toString(*it) + Separator);
        }
        return res;
    }

    //--------------------------------------------------------------------------------------------------------
    void Path::fromString(const std::string & str)
    {
        std::vector<std::string> parts;
        StringUtils::splitString(str, Separator, parts);
        clear();
        for (std::vector<std::string>::const_iterator it = parts.begin(); it != parts.end(); it++)
        {
            const std::string & value = (*it);
            if (!value.empty())
            {
                push_back(IsoDirectionConverter::getSingleton().fromString(value));
            }
        }
    }
} // namespace Core4