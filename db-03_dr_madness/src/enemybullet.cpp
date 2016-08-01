#include "enemybullet.hpp"
#include "util.hpp"

EnemyBullet::EnemyBullet(int x, int y, float dx, float dy, unsigned int damage, float drawingAngle)
	:Bullet(x, y, 5, 5, Entity::ENEMY_BULLET_TYPE, dx, dy, "bullet.bmp", 1),
	mAnimation("enemyshot.bmp"),
	mFrameCounter(0)
{

	mKillsPlayer = true;
}

void EnemyBullet::logic(Level* level)
{
	Bullet::logic(level);
	mFrameCounter++;
}

void EnemyBullet::draw(BITMAP *dest, int scrolly, unsigned int layer)
{
	mAnimation.drawFrame(dest, mFrameCounter / 3, mX, mY - scrolly);
}
