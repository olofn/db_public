#include "exception.hpp"


Exception::Exception()
    : mFunction("?"),
      mMessage(""),
      mFilename("?"),
      mLine(0)
{

}

Exception::Exception(const std::string& message)
    : mFunction("?"),
      mMessage(message),
      mFilename("?"),
      mLine(0)
{

}

Exception::Exception(const std::string& message,
                     const std::string& function,
                     const std::string& filename,
                     int line)
                     : mFunction(function),
                       mMessage(message),
                       mFilename(filename),
                       mLine(line)
{

}

const std::string& Exception::getFunction() const
{
    return mFunction;
}

const std::string& Exception::getMessage() const
{
    return mMessage;
}

const std::string& Exception::getFilename() const
{
    return mFilename;
}

int Exception::getLine() const
{
    return mLine;
}

