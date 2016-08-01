#if defined (__MINGW32__)
#define DB_WIN32
#define DB_DATA_PREFIX "data/"
#elif defined(_MSC_VER)
#define DB_WIN32
#define DB_DATA_PREFIX "data/"
#else
#define DB_UNIX
#define DB_DATA_PREFIX "data/"
#endif



