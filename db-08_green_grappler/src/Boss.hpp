#pragma once

#include "Entity.hpp"

class Animation;

class Boss :public Entity
{
public:
	Boss();
	void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
	void update();
	int getLayer();
	void setTilesCollidable(bool aCollidable);
	virtual void setRoom(Room *room);
	void onDamage();
	virtual Entity::CollisionRect getCollisionRect();
	bool isDamagable();
	void onRespawn();
private:
	Animation* myReactor;
	Animation* myBoss;
	int myHealth;
	int myInitalHealth;
	int myFrameCounter;
	enum State
	{
		State_Init,
		State_Sleeping,
		State_InitialBlow,
		State_Awakening,
		State_MoveUpwards,
		State_Float,
		State_Stop,
		State_Attack,
		State_Vulnerable,
		State_Dead
	};
	State myState;
	float2 myOriginalPos;
	Direction myDirection;
	int myAnimFrameCounter;
};