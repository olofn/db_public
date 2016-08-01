#ifndef NMC_GAMESTATE_HPP
#define NMC_GAMESTATE_HPP

#include <string>
#include <map>

namespace nmc
{
	class GameState
	{
	public:
		~GameState();

		GameState(const std::string &filename);

		GameState(const GameState &other);

		static GameState *getCurrent();

		static GameState *getSlot(int slot);

		void setInt(const std::string &key, int value);

		int getInt(const std::string &key);
        
        void setString(const std::string &key, const std::string& value);

		const std::string getString(const std::string &key);

		void clear();

		void save(const std::string &filename);

	private:
		bool load(const std::string &filename);

		std::map<std::string, int> mIntValues;
        std::map<std::string, std::string> mStringValues;
	};
}

#endif