#include <vector>
#include "Serialization/XmlDocument.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------------------------------------------------------
    const std::string XmlDocument::toString() const
    {
        TiXmlPrinter printer;
	    Accept(&printer);
        const char * dataPtr  = printer.CStr();
	    const size_t dataSize = printer.Size();
	    std::vector<char> data(dataSize);
	    memcpy(&data[0], dataPtr, dataSize);
        return std::string(data.begin(), data.end());
    }
} // namespace C4

