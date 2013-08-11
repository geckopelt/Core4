#include "Utils/Guards.hxx"
#include "Logging/Logger.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------
    Logger::Logger() : m_name("Log"), m_indent(0)
    {
        // reg<StdOutLogger>("STDOUT");
        // reg<HtmlLogger>("HTML");
    }

    //------------------------------------------------------------------------------
    Logger::~Logger()
    {
        cleanup();
    }

    //------------------------------------------------------------------------------
    void Logger::message(const ILogListener::Type type, const std::string & text)
    {
        for (LogListeners::iterator it = m_listeners.begin(); it != m_listeners.end(); it++)
        {
            if (NULL != it->second)
                it->second->message(type, m_indent, text);
        }
    }

    //------------------------------------------------------------------------------
    void Logger::addListener(const std::string & name)
    {
        CORE4_CHECK(m_listeners.find(name) == m_listeners.end(), "Log of type \"" + name + "\" already exists"); 
        ILogListener * listener = create(name);
        CORE4_CHECK(NULL != listener, "\"" + name + "\" is not a supported log type");
        m_listeners[name] = listener;
    }

    //------------------------------------------------------------------------------
    const std::string & Logger::getName() const
    {
        return m_name;
    }

    //------------------------------------------------------------------------------
    void Logger::setName(const std::string & name)
    {
        m_name = name;
    }

    //------------------------------------------------------------------------------
    void Logger::setIndent(const size_t indent)
    {
        m_indent = indent;
    }

    //------------------------------------------------------------------------------
    const size_t & Logger::getIndent() const
    {
        return m_indent;
    }

    //------------------------------------------------------------------------------
    void Logger::increaseIndent()
    {
        setIndent(getIndent() + IndentSize);
    }

    //------------------------------------------------------------------------------
    void Logger::decreaseIndent()
    {
        setIndent(getIndent() - IndentSize);
    }

    //------------------------------------------------------------------------------
    void Logger::cleanup()
    {
        for (LogListeners::iterator it = m_listeners.begin(); it != m_listeners.end(); it++)
        {
            delete it->second;
        }
        m_listeners.clear();
    }
} // namespace Core4
