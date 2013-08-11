#pragma once

/// @file Logger.hxx
/// @brief Logger

#include <map>
#include <string>
#include "Utils/Singleton.hxx"
#include "Utils/Factory.hxx"
#include "Logging/ILogListener.hxx"

namespace Core4
{
    /// A logger singleton class. Also implements a logger implementation factory.
    class Logger :
        public Singleton<Logger>,
        public Factory<std::string, ILogListener>
    {
    public:
        static const size_t IndentSize = 2;

        /// Ctor.
        Logger();

        /// Dtor.
        virtual ~Logger();

        /// Add a log listener.
        /// @param name Log implementation factory class name.
        void addListener(const std::string & name);

        /// Log a message to all logging implementations used.
        /// @param type Message type.
        /// @param text Message text.
        void message(const ILogListener::Type type, const std::string & text);

        /// Set a log name.
        /// @param name Log name.
        void setName(const std::string & name);

        /// Get a log name.
        /// @return —сылка на им€.
        const std::string & getName() const;

        /// Set current indent (in spaces).
        /// @param indent Indent in spaces.
        void setIndent(const size_t indent);

        /// Get current indent (in spaces).
        /// @return —абж.
        const size_t & getIndent() const;

        /// Increase current indent.
        void increaseIndent();

        /// Decrease current indent.
        void decreaseIndent();
    private:
        void cleanup();

        typedef std::map<std::string, ILogListener*> LogListeners;
        LogListeners m_listeners;

        std::string  m_name;
        size_t       m_indent;
    };

} // namespace Core4