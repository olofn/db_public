#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP
#include <map>
class GameState
{
public:
	GameState() { }

	void put(std::string key, int value);
	void put(std::string key, std::string value);
	void loadFromFile(const std::string &fileName = "gamestate.sav");
	void saveToFile(const std::string &fileName = "gamestate.sav");
	static bool isSavePresent(const std::string &fileName = "gamestate.sav");
	int getInt(std::string key);
	std::string getString(std::string key);
	void clear();

private:
	std::string getPrefix(const std::string &source);
	std::string getActualKey(const std::string &source);
	friend std::ostream& operator<<(std::ostream& s, GameState& gameState);

protected:
	std::map<std::string, std::string> mStrings;
	std::map<std::string, int> mInts;

};
std::ostream& operator<<(std::ostream& s, GameState& gameState);
#endif