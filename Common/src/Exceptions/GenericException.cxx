#include "Exceptions/GenericException.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------
    GenericException::GenericException(const std::string & message) : m_message(message) {}

    //------------------------------------------------------------------------------
    const char * GenericException::what() const { return m_message.c_str(); }
} // namespace Core4
