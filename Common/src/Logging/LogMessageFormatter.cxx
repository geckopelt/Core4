#include <sstream>
#include "Logging/LogMessageFormatter.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------
    const std::string LogMessageFormatter::formatMessage(ILogListener::Type type, const size_t indent, const std::string & text)
    {
        std::stringstream s;
        s << std::string(indent, ' ');
        switch (type)
        {
            case ILogListener::Error:
                s << "[Error] ";
                break;

            case ILogListener::Warning:
                s << "[Warning] ";
                break;

            case ILogListener::Other:
                s << "[*] ";
                break;

            default:
                break;
        }
        s << text;
        return s.str();
    }
} // namespace Core4
