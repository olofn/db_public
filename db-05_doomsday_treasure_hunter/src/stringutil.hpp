#ifndef NMC_STRINGUTIL_HPP
#define NMC_STRINGUTIL_HPP

#include <string>
#include <sstream>

template<typename T>
T fromString(const std::string& str)
{
    std::istringstream is(str);
    T t;
    is >> t;
    return t;
}

template<typename T>
std::string toString(T t)
{
    std::string str;
    std::ostringstream os(str);
    os << t;
    return os.str();
}

inline std::string convertSpaces(const std::string& str)
{
    std::string result;

    unsigned int i;
    for (i = 0; i < str.length(); i++)
    {
        if (str[i] == ' ')
        {
            result.append(std::string(1, '_'));
        }
        else
        {
            result.append(std::string(1, str[i]));
        }
    }

    return result;
}

inline std::string convertUnderscores(const std::string& str)
{
    std::string result;

    unsigned int i;
    for (i = 0; i < str.length(); i++)
    {
        if (str[i] == '_')
        {
            result.append(std::string(1, ' '));
        }
        else
        {
            result.append(std::string(1, str[i]));
        }
    }

    return result;
}

#endif
