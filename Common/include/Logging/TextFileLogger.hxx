#pragma once

/// @file TextFileLogger.hxx
/// @brief A simple text file logging implementation.

#include "Logging/ILogListener.hxx"

namespace Core4
{
    /// Text file logging implementation
    struct TextFileLogger : public ILogListener
    {
        /// @see ILogListener
        void message(const ILogListener::Type type, const size_t indent, const std::string & text);
    };
} // namespace Core4
