#ifndef NMC_GAMESTATEMANAGER_HPP
#define NMC_GAMESTATEMANAGER_HPP

#include "gamestate.hpp"

namespace nmc
{
	class GameStateManager
	{
	public:
		~GameStateManager();

		static GameStateManager *getInstance();

		GameState *getSlot(int slot);

		GameState *getCurrent();

		void loadSlot(int slot);

		void saveCurrent();

		void erase(int slot);

	private:
		GameStateManager();

		std::string toFilename(int slot);
		
		GameState *mCurrentState;
		int mCurrentSlot;
		GameState *mSlot[3];

		static GameStateManager *smInstance;		
	};
}

#endif