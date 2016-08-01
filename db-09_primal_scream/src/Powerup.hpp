#pragma once

#include "Entity.hpp"
#include "Animation.hpp"
class Font;

class Powerup : public Entity
{
private:
	Animation mAnimation;
	std::string mKind;
	int mFrame;

public:
	Powerup(std::string kind);

	virtual int getLayer() { return 1; };
	virtual void update();
	virtual void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
};