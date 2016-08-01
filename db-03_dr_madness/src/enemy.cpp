#include "enemy.hpp"

Enemy::Enemy(int x, int y, int width, int height, int hitCount)
: Entity(x, y, width, height, true)
{
	mHitCount = hitCount;
}