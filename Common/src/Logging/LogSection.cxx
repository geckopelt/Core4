#include "Logging/Logger.hxx"
#include "Logging/LogSection.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------
    LogSection::LogSection(const std::string & id) : m_id(id)
    {
        Logger::getSingleton().message(ILogListener::Info, id);
        Logger::getSingleton().message(ILogListener::Message, "{");
        Logger::getSingleton().setIndent(Logger::getSingleton().getIndent() + Logger::IndentSize);
    }

    //------------------------------------------------------------------------------
    LogSection::~LogSection()
    {
        Logger::getSingleton().setIndent(Logger::getSingleton().getIndent() - Logger::IndentSize);
        Logger::getSingleton().message(ILogListener::Message, "}");
    }
} // namespace Core4
