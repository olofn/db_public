#include "playerbullet.hpp"
#include "util.hpp"

PlayerBullet::PlayerBullet(int x, int y, float dx, float dy, unsigned int damage, float drawingAngle)
	:Bullet(x, y, 6, 6, Entity::PLAYER_BULLET_TYPE, dx, dy, "bullet.bmp", damage + 1),
	mAnimation("shot.bmp")
{
	mKillsPlayer = false;
	if (drawingAngle < 0)
	{
		vflip = false;
		drawingAngle = -drawingAngle;
	}
	else
	{
		vflip = true;
	}

	frame = (int)(drawingAngle * 5.4f / (M_PI / 2.0f));

	if (frame > 4) {
		frame = 4;
	}

	int d = std::min((int)damage - 1, 2);

	frame += 5 * d;
}


void PlayerBullet::draw(BITMAP *dest, int scrolly, unsigned int layer)
{
	mAnimation.drawFrame(dest, frame, mX - 2, mY -2 - scrolly, false, vflip);
}