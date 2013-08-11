#pragma once

/// @file StdOutLogger.hxx
/// @brief Standard output logging implementation.

#include "Logging/ILogListener.hxx"

namespace Core4
{
    /// Standard output logging implementation
    struct StdOutLogger : public ILogListener
    {
        /// @see ILogListener
        void message(const ILogListener::Type type, const size_t indent, const std::string & text);
    };
} // namespace Core4
