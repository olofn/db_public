#ifndef NMC_FILEUTIL_HPP
#define NMC_FILEUTIL_HPP

#include <fstream>
#include <string>

namespace nmc
{
	inline int readInt(std::istream &is)
	{
		int x;
		is.read((char *)&x, sizeof(x));
		return x;
	}

	inline void writeInt(std::ostream &os, int x)
	{
		os.write((char *)&x, sizeof(x));
	}

	inline void writeString(std::ostream &os, const std::string &s)
	{
		writeInt(os, s.size());
		os.write(s.c_str(), s.size());
	}

	inline std::string readString(std::istream &is)
	{
		int size = readInt(is);
		char *cstr = new char[size + 1];
		is.read(cstr, size);
		cstr[size] = '\0';
		std::string result(cstr);
		delete[] cstr;
		return result;
	}
}

#endif