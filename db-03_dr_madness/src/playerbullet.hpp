#ifndef DBSH07_PLAYERBULLET_HPP
#define DBSH07_PLAYERBULLET_HPP
#include <string>

#include "bullet.hpp"
#include "animation.hpp"

class PlayerBullet: public Bullet
{
public:
	PlayerBullet(int x, int y, float dx, float dy, unsigned int damage, float drawingAngle);

	void PlayerBullet::draw(BITMAP *dest, int scrolly, unsigned int layer);
protected:
	Animation mAnimation;
	int frame;
	bool vflip;
};

#endif