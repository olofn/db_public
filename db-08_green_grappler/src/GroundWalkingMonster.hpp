#pragma once

#include "Entity.hpp"

class Animation;

class GroundWalkingMonster : public Entity
{
public:
	enum Type
	{
		Type_Roof,
		Type_Floor,
		Type_LeftWall,
		Type_RightWall,
	};

	GroundWalkingMonster(
		Type aType);

	virtual int getLayer(){return 1;}

	virtual void update();
	virtual void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);

private:
	enum Facing
	{
		Facing_LeftUp,
		Facing_RightDown,
	} mDirection;

	Type mType;

	Animation* mAnimation;
	int mFrame;
};