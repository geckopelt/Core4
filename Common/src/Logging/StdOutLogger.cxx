#include <iostream>
#include "Logging/StdOutLogger.hxx"
#include "Logging/LogMessageFormatter.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------
    void StdOutLogger::message(const ILogListener::Type type, const size_t indent, const std::string & text)
    {
        std::cout << LogMessageFormatter::formatMessage(type, indent, text) << std::endl;
    }
} // namespace Core4
