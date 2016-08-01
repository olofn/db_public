#include <fstream>
#include "gamestate.hpp"
#include "exception.hpp"
#include "stringutil.hpp"
#include "fileutil.hpp"
#include "resourcehandler.hpp"
#include <iostream>

void GameState::put(std::string key, int value)
{
	//std::cout << "key: " << key << ", value: " << value << std::endl;
	mInts[key] = value;
	//std::cout << "now gamestate looks like this: " << std::endl << *this << std::endl;
}

void GameState::put(std::string key, std::string value)
{
	//std::cout << "key: " << key << ", value: " << value << std::endl;
	mStrings[key] = value;
	//std::cout << "now gamestate looks like this: " << std::endl << *this << std::endl;
}

int GameState::getInt(std::string key)
{
	return mInts[key];
}

std::string GameState::getString(std::string key)
{
	return mStrings[key];
}

void GameState::clear()
{
	mStrings.clear();
	mInts.clear();
}

bool GameState::isSavePresent(const std::string &fileName)
{
	try
	{
		std::string data = loadFile(fileName);
	}
	catch (Exception e)
	{
		return false;
	}

	return true; 
}

void GameState::loadFromFile(const std::string &fileName)
{
	clear();
	std::string data = loadFile(fileName);
	//std::cout << "data: " << data << std::endl;
	std::vector<std::string> mapTokens = tokenize(data, "\n", true);
	for(std::vector<std::string>::iterator iter = mapTokens.begin(); iter != mapTokens.end(); iter++ ) {
		std::vector<std::string> entryTokens = tokenize(*iter, "$=", true);
		if(entryTokens.size() == 2)
		{
			std::string keyWithPrefix = entryTokens[0];
			std::string value = entryTokens[1];
			//std::cout << "keyWithPrefix: " << keyWithPrefix << std::endl;
			//std::cout << "value: " << value << std::endl;

			std::string key = getActualKey(keyWithPrefix);
			std::string keyPrefix = getPrefix(keyWithPrefix);
			//std::cout << "key: " << key << std::endl;
			//std::cout << "keyPrefix: " << keyPrefix << std::endl;
			if(keyPrefix == "INT")
			{
				mInts[key] = stringToInt(value);
			}
			else if(keyPrefix == "STRING")
			{
				mStrings[key] = value;
			}
		}
	}
}

void GameState::saveToFile(const std::string &fileName)
{
	std::ofstream file;
	std::string realFilename = ResourceHandler::getInstance()->getRealFilename(fileName);
	file.open(realFilename.c_str(), std::ios::out);

	if (!file.is_open())
	{
		throw DB_EXCEPTION("Saves file could not be opened for save! " + fileName);
	}
	
	file << *this;

	file.close();
	
}

std::string GameState::getPrefix(const std::string &source)
{
	return source.substr(0, source.find("_"));
}

std::string GameState::getActualKey(const std::string &source)
{
	return source.substr(source.find("_")+1, source.length());
}

std::ostream& operator<<(std::ostream& s, GameState& gameState)
{
	for(std::map<std::string,int>::iterator iter = gameState.mInts.begin(); iter != gameState.mInts.end(); ++iter ) 
	{
		s << "INT_" << iter->first << "$=" << iter->second << "\n";
	}

	for(std::map<std::string,std::string>::iterator iter = gameState.mStrings.begin(); iter != gameState.mStrings.end(); ++iter ) 
	{
		s << "STRING_" << iter->first << "$=" << iter->second << "\n";
	}
	return s;
}