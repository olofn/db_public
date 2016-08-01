#include "exception.hpp"
#include "gamestatemanager.hpp"
#include "stringutil.hpp"
#include "os.hpp"

namespace nmc
{
	GameStateManager *GameStateManager::smInstance = NULL;	

	GameStateManager::GameStateManager()
	{
		mSlot[0] = new GameState(toFilename(0));
		mSlot[1] = new GameState(toFilename(1));
		mSlot[2] = new GameState(toFilename(2));

		mCurrentSlot = -1;		
		mCurrentState = NULL;
	}

	GameStateManager::~GameStateManager()
	{
		delete mSlot[0];
		delete mSlot[1];
		delete mSlot[2];

		if (mCurrentSlot != NULL)
		{
			delete mCurrentState;
		}
	}

	GameStateManager *GameStateManager::getInstance()
	{
		if (smInstance == NULL)
		{
			smInstance = new GameStateManager();
		}

		return smInstance;
	}

	GameState *GameStateManager::getSlot(int slot)
	{
		return mSlot[slot];
	}

	GameState *GameStateManager::getCurrent()
	{
		if (mCurrentState == NULL)
		{
			throw NMC_EXCEPTION("No state loaded");
		}

		return mCurrentState;
	}

	void GameStateManager::loadSlot(int slot)
	{
		if (mCurrentState != NULL)
		{
			delete mCurrentState;
		}

		mCurrentState = new GameState(*mSlot[slot]);
		mCurrentSlot = slot;

        if (mCurrentState->getInt("empty") == 1)
        {
            // Prepare new game
            mCurrentState->setInt("empty", 0);
            mCurrentState->setInt("roomNumber", 1);
			mCurrentState->setInt("maxHealth", 12);
			mCurrentState->setInt("maxMana", 12);
        }
	}

	void GameStateManager::saveCurrent()
	{
		delete mSlot[mCurrentSlot];
		mSlot[mCurrentSlot] = new GameState(*mCurrentState);
		mSlot[mCurrentSlot]->save(toFilename(mCurrentSlot));
	}

	void GameStateManager::erase(int slot)
	{
		mSlot[slot]->clear();
		mSlot[slot]->save(toFilename(slot));
	}

	std::string GameStateManager::toFilename(int slot)
	{
		return NMC_SAVE_PREFIX + "save" + toString(slot) + ".dat";
	}
}