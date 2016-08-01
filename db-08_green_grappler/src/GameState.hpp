#pragma once

class GameState
{
public:
	static void put(std::string key, int value);
	static void put(std::string key, std::string value);
	static void loadFromFile(const std::string &fileName = "gamestate.sav");
	static void saveToFile(const std::string &fileName = "gamestate.sav");
	static bool isSavePresent(const std::string &fileName = "gamestate.sav");
	static int getInt(std::string key);
	static std::string getString(std::string key);
	static void clear();

private:
	GameState() { }

	static std::string getPrefix(const std::string &source);
	static std::string getActualKey(const std::string &source);

protected:
	static std::map<std::string, std::string> mStrings;
	static std::map<std::string, int> mInts;

};