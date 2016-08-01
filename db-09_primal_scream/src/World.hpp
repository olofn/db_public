#pragma once

#include "Screen.hpp"

class Room;
class Font;
class Animation;

class World : public Screen
{
private:
	Room *myCurrentRoom;
	bool pendingRoomLoad;
	float2 roomLoadWorldPos;
	bool ended;
	
	void doLoadRoom();
	
public:
	World();
	~World();
	void loadRoom(float2 worldPos);
	virtual void onDraw(BITMAP* aBuffer);
	virtual void onLogic();
	void respawn(bool useSaveFile);
	void endGame();

	void onNormalLogic();
	void onExitLogic();

	void onNormalDraw(BITMAP* aBuffer);
	void onExitDraw(BITMAP* aBuffer);
	bool myExit;
	Font* myFont;
	int mySelected;
	Animation* myHand;
	Animation* myFade;
	bool myFirstHeroSpawn;

};