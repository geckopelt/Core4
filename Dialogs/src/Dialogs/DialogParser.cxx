#include <algorithm>
#include "Dialogs/DialogParser.hxx"

namespace Core4
{
    bool isWhitespace(wchar_t c)
    {
        return (c == '\t' || c == '\r' || c == '\n' );
    }

    //--------------------------------------------------------------------------------------------------------------------------
    std::list<DialogNode> DialogParser::parseDialogScript(const std::wstring & script)
    {
        std::wstring chat(script);    
        std::replace_if(chat.begin(), chat.end(), isWhitespace, ' ');

        std::wstring token;
        while (!chat.empty())
        {

            // TODO
        }

        // TODO
        return std::list<DialogNode>();
    }
} // namespace Core4
