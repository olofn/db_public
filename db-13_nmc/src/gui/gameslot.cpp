#include "gui/gameslot.hpp"

#include "gamestatemanager.hpp"
#include "resourcehandler.hpp"

namespace nmc
{
    GameSlot::GameSlot()
    {
        setOpaque(false);
        setSize(200, 50);

        mFont = new gcn::ImageFont(ResourceHandler::getInstance()->getRealFilename("gamefont2.bmp"), 
                                   32, 
                                   126);

        

        mAreaLabel = new gcn::Label();
        mAreaLabel->setFont(mFont);
        add(mAreaLabel, 40, 5);
    }

    void GameSlot::update(int slotNumber)
    {
        GameState* gameState = GameStateManager::getInstance()->getSlot(slotNumber);

        if (gameState->getInt("empty") == 1)
        {
            mAreaLabel->setCaption("Empty");
        }
        else
        {
            mAreaLabel->setCaption(gameState->getString("area"));
        }
        
        mAreaLabel->adjustSize();
    }

    GameSlot::~GameSlot()
    {
        delete mAreaLabel;
        delete mFont;
    }
}