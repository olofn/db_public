#include <fstream>
#include <allegro.h>

#include "gamestate.hpp"
#include "fileutil.hpp"
#include "exception.hpp"
#include "os.hpp"
#include "stringutil.hpp"

namespace nmc
{
	GameState::GameState(const std::string &filename)
	{
		if (!load(filename))
		{
			setInt("empty", 1);
		}
	}

	GameState::GameState(const GameState &other)
	{
		std::map<std::string, int>::const_iterator itInt;

		for (itInt = other.mIntValues.begin(); itInt != other.mIntValues.end(); itInt++)
		{
			mIntValues[itInt->first] = itInt->second;
		}

		std::map<std::string, std::string>::const_iterator itString;

		for (itString = other.mStringValues.begin(); itString != other.mStringValues.end(); itString++)
		{
			mStringValues[itString->first] = itString->second;
		}
	}

	GameState::~GameState()
	{
	}

	void GameState::setInt(const std::string &key, int value)
	{
		mIntValues[key] = value;
	}

	int GameState::getInt(const std::string &key)
	{
		if (mIntValues.find(key) == mIntValues.end())
		{
			return 0;
		}

		return mIntValues[key];
	}

    void GameState::setString(const std::string &key, const std::string& value)
	{
		mStringValues[key] = value;
	}

	const std::string GameState::getString(const std::string &key)
	{
		if (mStringValues.find(key) == mStringValues.end())
		{
			return "";
		}

		return mStringValues[key];
	}

	void GameState::save(const std::string &filename)
	{
		std::ofstream file(filename.c_str(), std::ios_base::out | std::ios_base::binary);

		if (!file.is_open() || !file.good())
		{
			file.close();
			throw NMC_EXCEPTION("Unable to open " + filename + " for writing.");
		}

		writeInt(file, mIntValues.size());

		std::map<std::string, int>::iterator itInt;
		for (itInt = mIntValues.begin(); itInt != mIntValues.end(); itInt++)
		{
			writeString(file, itInt->first);
			writeInt(file, itInt->second);
		}

        writeInt(file, mStringValues.size());

		std::map<std::string, std::string>::iterator itString;
		for (itString = mStringValues.begin(); itString != mStringValues.end(); itString++)
		{
			writeString(file, itString->first);
			writeString(file, itString->second);
		}

		file.close();
	}

	bool GameState::load(const std::string &filename)
	{
		if (!exists(filename.c_str()))
		{
			return false;
		}

		std::ifstream file(filename.c_str(), std::ios_base::in | std::ios_base::binary);
	
		if (!file.is_open() || !file.good())
		{
			file.close();
			throw NMC_EXCEPTION("Unable to open " + filename + " for reading.");
		}

		mIntValues.clear();

		int size = readInt(file);
		int i;
		for (i = 0; i < size; i++)
		{
			std::string key = readString(file);
			int value = readInt(file);
			mIntValues[key] = value;
		}

        mStringValues.clear();

		size = readInt(file);
		for (i = 0; i < size; i++)
		{
			std::string key = readString(file);
            std::string value = readString(file);
			mStringValues[key] = value;
		}

		file.close();

		return true;
	}

	void GameState::clear()
	{
		mStringValues.clear();
		mIntValues.clear();
		mIntValues["empty"] = 1;
	}
}
