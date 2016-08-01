#ifndef NMC_STRINGUTIL_HPP
#define NMC_STRINGUTIL_HPP

#include <string.h>
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

inline std::string toUpperCase(const std::string& str)
{
    std::stringstream ss;

  for (int i = 0; i < str.size(); i++)
    {
      ss << (char)toupper(str[i]);
    }
  return ss.str();
  //return toupper(str);//std::string(_strupr((char *)str.c_str()));
}

inline int stringToInt(const std::string &str) {
	std::stringstream ss(str);
  int num;
  if((ss >> num).fail())
  { 
      return 0;
  }
  return num;
}


#endif
