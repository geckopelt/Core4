#include <fstream>
#include "Logging/Logger.hxx"
#include "Logging/TextFileLogger.hxx"
#include "Logging/LogMessageFormatter.hxx"
#include "Configuration/Configuration.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------
    void TextFileLogger::message(const ILogListener::Type type, const size_t indent, const std::string & text)
    {
        std::ofstream(Configuration::getSingleton().getLogPath(), std::ios_base::app) 
            << LogMessageFormatter::formatMessage(type, indent, text) << std::endl;
    }
} // namespace Core4
