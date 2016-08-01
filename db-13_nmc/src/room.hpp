#ifndef NMC_ROOM_HPP
#define NMC_ROOM_HPP

#include <allegro.h>
#include <list>

#include "guichan.hpp"
#include "tilemap.hpp"
#include "entity.hpp"
#include "animation.hpp"
#include "entities/player.hpp"
#include "entities/camera.hpp"
#include "gui/dialog.hpp"
#include "gui/savedialog.hpp"
#include "keystate.hpp"

namespace nmc
{
    class Room
    {
    public:
        Room(gcn::Gui* gui);
        ~Room();
        void load(unsigned int roomNumber);
        void draw(BITMAP* dest);
		void logic();

		TileMap *getTileMap();
		void addEntity(Entity *entity);
		Player *getPlayer();
		Camera *getCamera();
        Dialog* getDialog();
        SaveDialog* getSaveDialog();
        gcn::TextBox* getTextBox();

        const std::list<Entity*>& getEntityList();

		const KeyState &getKeyState();

		bool isKeysDisabled();

		void setKeysDisabled(bool keysDisabled);

		void disablePlayer();

		void enablePlayer();

    protected:
		void moveToNewRoomIfNeeded();

		void drawFade(BITMAP *dest, int amount);

		void loadEntities();

        TileMap* mTileMap;
		Player *mPlayer;
		Camera *mCamera;
		std::list<Entity *> mEntities;
		int mFadeCounter;
		int mFadeDirection;
		int mFadeOut;
		int mNextRoom;
		int mNextPlayerX, mNextPlayerY;
		Animation mFadeAni;
        gcn::Gui* mGui;
        Dialog* mDialog;
        SaveDialog* mSaveDialog;
        gcn::TextBox* mTextBox;
        gcn::ImageFont* mFont;
		KeyState mKeyState;
		bool mPlayerDisabled;
        Animation mHeartAnimation;
        Animation mManaAnimation;
    };
}
#endif