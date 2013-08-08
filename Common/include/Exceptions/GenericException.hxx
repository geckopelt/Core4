#pragma once

/// @file GenericException.hxx
/// @brief Generic Core4 exception class

#include <stdexcept>

namespace Core4
{

/// Generic Core4 exception class.
class GenericException : public std::exception
{
public:
    /// Ctor.
    /// @param message Error message.
    GenericException(const std::string & message);

    /// @see std::exception
    virtual const char * what() const;

private:
    std::string m_message;
};

} // namespace Core4