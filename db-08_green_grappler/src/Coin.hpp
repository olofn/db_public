#pragma once

#include "Entity.hpp"

class Animation;

class Coin : public Entity
{
public:
	Coin();

	virtual void setLifeTime(int aLifeTime);

	static void SpawnDeathCoins( int aNumberOfCoins, float2 aCenterPosition, int aLifeTime, Room* aRoom);

	virtual int getLayer(){return 0;}

	virtual void update();
	virtual void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
	virtual void onRespawn();

private:

	enum Type
	{
		Type_Static,
		Type_Dynamic,
	} mType;

	int mLifeTime;
	bool mTemporary;

	int mFrame;
	Animation* mAminationCoin;
};