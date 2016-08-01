#pragma once

#include "Entity.hpp"
#include "Animation.hpp"

class Font;

class Savepoint : public Entity
{
private:
	Animation mAnimation;
	int mTextCounter;
	bool mHeroOn;
	int mFrame;
	Font *mFont;

public:
	Savepoint();

	virtual int getLayer() { return 1; };
	virtual void update();
	virtual void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
};