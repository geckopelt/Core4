#include <stdarg.h>
#include <algorithm>
#include <iterator>
#include <sstream>
#include "Utils/StringUtils.hxx"

namespace Core4
{
    namespace
    {
        template <typename T> const std::string toString(T in)
        {
            std::ostringstream s;
            s << in;
            return s.str();
        }
    }

    //------------------------------------------------------------------------------
    const std::string StringUtils::intToString(int i)
    {
        return toString<int>(i);
    }

    //------------------------------------------------------------------------------
    const std::string StringUtils::floatToString(float f)
    {
        return toString<float>(f);
    }
  
    //------------------------------------------------------------------------------
    const std::string StringUtils::toUpper(const std::string & str)
    {
        std::string result;
	    std::transform(str.begin(), str.end(), std::back_inserter(result), ::toupper);
	    return result;
    }

    //------------------------------------------------------------------------------
    const std::string StringUtils::toLower(const std::string & str)
    {
        std::string result;
	    std::transform(str.begin(), str.end(), std::back_inserter(result), ::tolower);
	    return result;
    }

    //------------------------------------------------------------------------------
    void StringUtils::splitString(const std::string & str, const std::string & separator, std::vector<std::string> & out)
    {
        std::string temp(str);
        while (1)
        {
            size_t pos = temp.find(separator);
            if (pos == std::string::npos)
                break;

            std::string sub = temp.substr(0, pos);
            out.push_back(sub);
            temp.erase(0, pos + separator.length());
        }
        if (temp.length() > 0)
            out.push_back(temp);
    }
} // namespace Core4
