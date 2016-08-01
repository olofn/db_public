#ifndef DBSH07_EXCEPTION_HPP
#define DBSH07_EXCEPTION_HPP

#include <string>

#ifdef _MSC_VER
#if _MSC_VER <= 1200
#define __FUNCTION__ "?"
#endif
#endif

/*
 * A macro to be used when throwing exceptions.
 * What it basicly does is that it creates a new exception
 * and automatically sets the filename and line number where
 * the exception occured.
 */
#define DBSH07_EXCEPTION(mess) Exception(mess,   \
                            __FUNCTION__,          \
                            __FILE__,              \
                            __LINE__)

/**
 * An exception containing a message, a file and a line number.
 * Guichan will only throw exceptions of this class. You can use
 * this class for your own exceptions. A nifty feature of the
 * excpetion class is that it can tell you from which line and
 * file it was thrown. To make things easier when throwing
 * exceptions there exists a macro for creating exceptions
 * which automatically sets the filename and line number.
 *
 * EXAMPLE: @codeDBSH07_EXCEPTION("my error message");
 *          @endcode
 */
class Exception
{
public:

    /**
     * Constructor.
     */
    Exception();

    /**
     * Constructor.
     *
     * @param message the error message.
     */
    Exception(const std::string& message);

    /**
     * Constructor.
     *
     * NOTE: Don't use this constructor. Use the DBSH07_EXCEPTION macro instead.
     *
     * @param message the error message.
     * @param function the function name.
     * @param filename the name of the file.
     * @param line the line number.
     */
    Exception(const std::string& message,
              const std::string& function,
              const std::string& filename,
              int line);

    /**
     * Gets the function name in which the exception was thrown.
     *
     * @return the function name in which the exception was thrown.
     */
    const std::string& getFunction() const;

    /**
     * Gets the error message of the exception.
     *
     * @return the error message.
     */
    const std::string& getMessage() const;

    /**
     * Gets the filename in which the exceptions was thrown.
     *
     * @return the filename in which the exception was thrown.
     */
    const std::string& getFilename() const;

    /**
     * Gets the line number of the line where the exception was thrown.
     *
     * @return the line number of the line where the exception was thrown.
     */
    int getLine() const;

protected:
    std::string mFunction;
    std::string mMessage;
    std::string mFilename;
    int mLine;
};

#endif 

