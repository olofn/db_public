#include <allegro.h>

#include "room.hpp"
#include "exception.hpp"
#include "os.hpp"
#include "resourcehandler.hpp"
#include "gamestatemanager.hpp"
#include "world.hpp"
#include "entityfactory.hpp"
#include "entities/player.hpp"

namespace nmc
{
	static const int FADE_TIME = 15;

    Room::Room(gcn::Gui* gui) 
        : mFadeAni("fade.bmp"),
          mGui(gui),
		  mPlayerDisabled(false),
          mHeartAnimation("heart.bmp", 5),
          mManaAnimation("mana.bmp", 5)
    {
        mTileMap = new TileMap();
		mPlayer = new Player();
		mFadeCounter = 0;
		mFadeOut = false;

        mFont = new gcn::ImageFont(ResourceHandler::getInstance()->getRealFilename("gamefont2.bmp"), 32, 127);
        mFont->setGlyphSpacing(-2);

        mDialog = new Dialog();
        mDialog->setSize(310, 75);
        mDialog->setVisible(false);
        static_cast<gcn::Container*>(mGui->getTop())->add(mDialog, 5, 5);

        mSaveDialog = new SaveDialog();
        mSaveDialog->setVisible(false);
        static_cast<gcn::Container*>(mGui->getTop())->add(mSaveDialog, 
                                                          160 - mSaveDialog->getWidth() / 2, 
                                                          170);

        mTextBox = new gcn::TextBox();
        mTextBox->setVisible(false);
        mTextBox->setEditable(false);
        mTextBox->setOpaque(false);
        mTextBox->setBorderSize(0);
        mTextBox->setFont(mFont);
        static_cast<gcn::Container*>(mGui->getTop())->add(mTextBox);
    }

    Room::~Room()
    {
        delete mTileMap;
		delete mPlayer;
        delete mDialog;
        delete mTextBox;
        delete mFont;
    }

    void Room::load(unsigned int roomNumber)
    {	
		std::list<Entity *>::iterator it;

		for (it = mEntities.begin(); it != mEntities.end(); it++)
		{
			if ((*it) != mPlayer)
			{
				delete (*it);
			}
		}

		mEntities.clear();

        mTileMap->load(roomNumber);
		
		loadEntities();

		GameStateManager::getInstance()->getCurrent()->setInt("roomNumber", roomNumber);
		
		// Prepare the key state to avoid player jump after menu
		mKeyState.setDisabled(false);
		mKeyState.setKeys(key[KEY_UP], key[KEY_DOWN], key[KEY_LEFT], key[KEY_RIGHT],
		                  key[KEY_LCONTROL], key[KEY_ALT], key[KEY_LSHIFT]);
		mTextBox->setVisible(false);
    }

	void Room::loadEntities()
	{
		mCamera = new Camera();		
		mEntities.clear();
		mPlayer->setPosition(100, 100);
		mCamera->setTarget(mPlayer);
		mEntities.push_back(mPlayer);
		mEntities.push_back(mCamera);

		int x, y;
		for (x = 0; x < mTileMap->getWidth(); x++)
		{
			for (y = 0; y < mTileMap->getHeight(); y++)
			{
				int e = mTileMap->getTileEntity(x, y);
				if (e != 0)
				{
					if (e == 1)
					{
						mPlayer->setPosition(x * 16 + 8, y * 16 - 16);
					}
					else
					{
						mEntities.push_back(EntityFactory::getInstance()->createEntity(e, x * 16, y * 16));
					}
				}
			}
		}
		
		mCamera->moveToTarget(mTileMap);

		std::list<Entity *>::iterator it;

		for (it = mEntities.begin(); it != mEntities.end(); it++)
		{
			(*it)->initialize(this);
		}
	}

    void Room::draw(BITMAP* dest)
    {	
		int scrollx = mCamera->getX();
		int scrolly = mCamera->getY();

        std::list<Entity *>::iterator it;

        for (it = mEntities.begin(); it != mEntities.end(); it++)
		{
            if ((*it)->drawInLayer(Entity::BACKGROUND_LAYER))
            {
			    (*it)->draw(dest, scrollx, scrolly, Entity::BACKGROUND_LAYER);
            }
		}

        mTileMap->draw(dest, scrollx, scrolly, TileMap::BACKGROUND_LAYER);

		for (it = mEntities.begin(); it != mEntities.end(); it++)
		{
            if ((*it)->drawInLayer(Entity::PLAYER_LAYER))
            {
			    (*it)->draw(dest, scrollx, scrolly, Entity::PLAYER_LAYER);
            }
		}

       mTileMap->draw(dest, scrollx, scrolly, TileMap::FOREGROUND_LAYER);

        for (it = mEntities.begin(); it != mEntities.end(); it++)
		{
            if ((*it)->drawInLayer(Entity::FOREGROUND_LAYER))
            {
			    (*it)->draw(dest, scrollx, scrolly, Entity::FOREGROUND_LAYER);
            }
		}

		if (mFadeOut) 
        {
			drawFade(dest, FADE_TIME - mFadeCounter);
			//rectfill(dest, 0, 0, 320 - (mFadeCounter * 320) / FADE_TIME, 240, makecol(0,0,0));
		} else if (mFadeCounter > 0) {
			drawFade(dest, mFadeCounter);
			//rectfill(dest, 320 - (mFadeCounter * 320) / FADE_TIME, 0, 320, 240, makecol(0,0,0));
		}

        int i;
        int health = mPlayer->getHealth();
		if (health < 0)
		{
			health = 0;
		}

        for (i = 0; i < mPlayer->getMaximumHealth() / 4; i++)
        {
            if (health >= 4)
            {
                mHeartAnimation.drawFrame(dest, 4, 5 + i * mHeartAnimation.getFrameWidth(), 5);
                health -= 4;
            }
            else
            {
                mHeartAnimation.drawFrame(dest, health, 5 + i * mHeartAnimation.getFrameWidth(), 5);
                health = 0;
            }
        }

        line(dest, 
             7, 
             6 + mHeartAnimation.getFrameHeight(),
             7,
             6 + mHeartAnimation.getFrameHeight() + mManaAnimation.getFrameHeight() - 1,
             makecol(255, 255 , 255));
        line(dest, 
             8 + mManaAnimation.getFrameWidth() * mPlayer->getMaximumMana() / 4, 
             6 + mHeartAnimation.getFrameHeight(),
             8 + mManaAnimation.getFrameWidth() * mPlayer->getMaximumMana() / 4,
             6 + mHeartAnimation.getFrameHeight() + mManaAnimation.getFrameHeight() - 1,
             makecol(255, 255 , 255));

        int mana = mPlayer->getMana();
		if (mana < 0)
		{
			mana = 0;
		}

        for (i = 0; i < mPlayer->getMaximumMana() / 4; i++)
        {
            if (mana >= 4)
            {
                mManaAnimation.drawFrame(dest, 
                                         4, 
                                         8 + i * mManaAnimation.getFrameWidth(), 
                                         6 + mHeartAnimation.getFrameHeight());
                mana -= 4;
            }
            else
            {
                mManaAnimation.drawFrame(dest, 
                                         mana, 
                                         8 + i * mManaAnimation.getFrameWidth(), 
                                         6 + mHeartAnimation.getFrameHeight());
                mana = 0;
            }
        }
    }

	void Room::drawFade(BITMAP *dest, int amount) {
		int x, y;
		for (x = 0; x < dest->w; x += mFadeAni.getFrameWidth())
		{
			for (y = 0; y < dest->w; y += mFadeAni.getFrameHeight())
			{
				mFadeAni.drawFrame(dest, amount, x, y);
			}
		}
	}

	// Predicate function used to remove entities.
	static bool isNull(Entity *e) {
		return e == NULL;
	}

	void Room::logic()
	{

		mKeyState.setKeys(key[KEY_UP], key[KEY_DOWN], key[KEY_LEFT], key[KEY_RIGHT],
		                  key[KEY_LCONTROL], key[KEY_ALT], key[KEY_LSHIFT]);	


		if (mFadeCounter == 0 && mFadeOut)
		{
			mFadeCounter = FADE_TIME;
			mFadeOut = false;
			load(mNextRoom);
			mPlayer->setPosition(mNextPlayerX, mNextPlayerY);
			mCamera->moveToTarget(mTileMap);
			return;
		}
		if (mFadeCounter > 0) {
			mFadeCounter--;
			return;
		}

		std::list<Entity *>::iterator it1, it2;

		for (it1 = mEntities.begin(); it1 != mEntities.end(); it1++)
		{
			(*it1)->logic(this);
		}

        for (it1 = mEntities.begin(); it1 != mEntities.end(); it1++)
		{
			if ((*it1)->isToBeDeleted()) {
				delete (*it1);
				*it1 = NULL;
			}
		}

		mEntities.remove_if(isNull);

		for (it1 = mEntities.begin(); it1 != mEntities.end(); it1++)
		{
			for (it2 = it1; it2 != mEntities.end(); it2++)
			{
				Entity *e1 = *it1;
				Entity *e2 = *it2;

				if (e1 != e2 && e1->isCollidable() && e2->isCollidable() && e1->collidesWith(e2))
				{
					e1->handleCollision(e2, this);
					e2->handleCollision(e1, this);
				}	
			}
		}

		for (it1 = mEntities.begin(); it1 != mEntities.end(); it1++)
		{
			if ((*it1)->isToBeDeleted()) {
				delete (*it1);
				*it1 = NULL;
			}
		}

		mEntities.remove_if(isNull);
		
		moveToNewRoomIfNeeded();
	}

	void Room::moveToNewRoomIfNeeded()
	{
		int x = mPlayer->getCenterX(), y = mPlayer->getCenterY();
		if (!(x < 0 || y < 0 || x >= mTileMap->getWidth() * 16 || y >= mTileMap->getHeight() * 16))
		{
			return; // We are still in the same room
		}

		World *world = World::getInstance();
		
		int currentRoom = GameStateManager::getInstance()->getCurrent()->getInt("roomNumber");
		
		int worldX = x + world->getRoomPosition(currentRoom).x * 16;
		int worldY = y + world->getRoomPosition(currentRoom).y * 16;

		int newRoom = world->getRoomAt(worldX / 16, worldY / 16);
		
		x = worldX - world->getRoomPosition(newRoom).x * 16;
		y = worldY - world->getRoomPosition(newRoom).y * 16;

		mNextRoom = newRoom;
		mNextPlayerX = x - mPlayer->getWidth() / 2;
		mNextPlayerY = y - mPlayer->getHeight() / 2;

		mFadeCounter = FADE_TIME;
		mFadeOut = true;
	}

	TileMap *Room::getTileMap()
	{
		return mTileMap;
	}

	void Room::addEntity(Entity *entity)
	{
		mEntities.push_back(entity);
	}

	Player *Room::getPlayer()
	{
		return mPlayer;
	}

	Camera *Room::getCamera()
	{
		return mCamera;
	}

    const std::list<Entity*>& Room::getEntityList()
    {
        return mEntities;
    }

    Dialog* Room::getDialog()
    {
        return mDialog;
    }

    SaveDialog* Room::getSaveDialog()
    {
        return mSaveDialog;
    }

    gcn::TextBox* Room::getTextBox()
    {
        return mTextBox;
    }

	const KeyState &Room::getKeyState()
	{
		return mKeyState;
	}

	bool Room::isKeysDisabled()
	{
		return mKeyState.isDisabled();
	}

	void Room::setKeysDisabled(bool keysDisabled)
	{
		mKeyState.setDisabled(keysDisabled);
	}

	void Room::disablePlayer()
	{
		if (mPlayerDisabled)
		{
			return;
		}

		mEntities.remove(mPlayer);
		mPlayerDisabled = true;
	}

	void Room::enablePlayer()
	{
		if (!mPlayerDisabled)
		{
			return;
		}

		mEntities.push_front(mPlayer);
		mPlayerDisabled = false;
	}
}