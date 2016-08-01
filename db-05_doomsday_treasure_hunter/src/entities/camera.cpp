#include "entities/camera.hpp"

#include "level.hpp"

Camera::Camera() 
    : Entity(false),
	    mPlayer(NULL)
{
}

Camera::~Camera()
{
}

void Camera::setTarget(Player *player)
{
	mPlayer = player;
}

void Camera::moveToTarget(TileMap *tileMap)
{
	if (mPlayer != NULL)
	{
		setPosition(mPlayer->getCenterX() - 160, mPlayer->getCenterY() - 140);
	}

	clampToMapEdges(tileMap);
}

void Camera::logic(Level *level)
{
	TileMap *tileMap = level->getTileMap();

	if (mPlayer == NULL)
	{
		return;
	}

	int targetX, targetY;

	targetX = mPlayer->getCenterX() - 160;
	
	if (mPlayer->getState() == Player::GROUND || mPlayer->getJumpY() < mPlayer->getCenterY()) {
		targetY = mPlayer->getCenterY() - 140;
	} else {			
		targetY = mPlayer->getJumpY() - 140;
	}

	if (targetY < 0)
	{
		targetY = 0;
	}

	if (targetY >= tileMap->getHeight() * 16 + 16 - 240)
	{
		targetY = tileMap->getHeight() * 16 + 16 - 240;
	}

	int dx = (targetX - mX) / 4;
	int dy = targetY - mY;

	if (dy < 0) {
		dy /= 12;
		dy--;
	} else if (dy > 0) {
		dy /= 12;
		dy++;
	}
	
	mX += dx;

	if (dy < 7 && dy > -7) {
		mY += dy;
	} else {
		if (dy < 0) {
			mY -= 7;
		} else {
			mY += 7;
		}
	}

	clampToMapEdges(tileMap);
}

void Camera::draw(BITMAP *dest, int scrollX, int scrollY, unsigned int layer)
{
}

bool Camera::isToBeDeleted()
{
	return false;
}

void Camera::clampToMapEdges(TileMap *tileMap)
{
	if (mX < 0)
	{
		mX = 0;
	}

	if (mY < 0)
	{
		mY = 0;
	}

	if (mX >= tileMap->getWidth() * 16 - 320)
	{
		mX = tileMap->getWidth() * 16 - 320;
	}

	if (mY >= tileMap->getHeight() * 16 + 16 - 240)
	{
		mY = tileMap->getHeight() * 16 + 16 - 240;
	}
}
