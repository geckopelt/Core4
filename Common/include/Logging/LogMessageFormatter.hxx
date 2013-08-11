#pragma once

/// @file LogMessageFormatter.hxx
/// @brief A class to format log messages.

#include <string>
#include "ILogListener.hxx"

namespace Core4
{
    /// Log message formatter.
    struct LogMessageFormatter
    {
        /// Format a log message.
        /// @param type Message type.
        /// @param indent Indent in spaces.
        /// @param text Message text.
        static const std::string formatMessage(ILogListener::Type type, const size_t indent, const std::string & text);
    };
} // namespace Core4