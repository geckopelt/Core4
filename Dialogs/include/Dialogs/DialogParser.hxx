/// @file DialogParser.hxx
/// @brief Dialog scripts parser

#ifndef DIALOG_PARSER_HXX
#define DIALOG_PARSER_HXX

#include <list>
#include "Dialogs/DialogNode.hxx"

namespace Core4
{
    /// Dialog script parser class
    class DialogParser
    {
    public:
        // TODO document
        static std::list<DialogNode> parseDialogScript(const std::wstring & script);
    };
} // namespace Core4

#endif