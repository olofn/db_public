#include "Precompiled.hpp"

#include "Room.hpp"
#include "Resource.hpp"
#include "Entity.hpp"
#include "Hero.hpp"
#include "World.hpp"
#include "Layer.hpp"
#include "Tile.hpp"
#include "Camera.hpp"
#include "Font.hpp"
#include "Input.hpp"
#include "Music.hpp"
#include "ParticleSystem.hpp"

#include <stdio.h>

using namespace std;


Room::Room(Layer* aTileLayer, int aWorldOffsetX, int aWorldOffsetY)
	: mTileLayer(aTileLayer)
	, mHero(0)
	, myHeroIsDead(false)
	, myIsCompleted(false)
	, myWorldOffsetX(aWorldOffsetX)
	, myWorldOffsetY(aWorldOffsetY)
{
	myFont = Resource::getFont("data/images/font.bmp");
}

Room::~Room() {
	delete mTileLayer;
}

void Room::setWorld(World *aWorld)
{
	myWorld = aWorld;
}

void Room::onDraw( BITMAP* aBuffer )
{
	clear_to_color(aBuffer, makecol(0x44, 0x66, 0x88));

	if (mHero->isDead())
	{
		if (myFrameCounter == 0 || myFrameCounter == 5 || myFrameCounter == 10)
			rectfill(aBuffer, 0, 0, 320, 240, makecol(128,64,64));
		else
			rectfill(aBuffer, 0, 0, 320, 240, makecol(0,0,0));
		
		if (myFrameCounter < 60)
			mHero->draw(aBuffer, mCamera->getOffset().x, mCamera->getOffset().y, 0);
		return;
	}

	for (int layer = 0; layer < 1; layer++)
	{
		for (int i = 0; i < (int)mEntities.size(); i++)
		{
			if (mEntities[i]->getLayer() != layer)
				continue;

			mEntities[i]->draw(aBuffer, mCamera->getOffset().x, mCamera->getOffset().y, 0);
		}
	}

	privDrawLayer(aBuffer, mTileLayer);

	for (int layer = 1; layer < 5; layer++)
	{
		for (int i = 0; i < (int)mEntities.size(); i++)
		{
			if (mEntities[i]->getLayer() != layer)
				continue;

			mEntities[i]->draw(aBuffer, mCamera->getOffset().x, mCamera->getOffset().y, 0);
		}
	}

	/*
	for (int i = 0; i < (int)mEntities.size(); i++)
	{
		Entity::CollisionRect r = mEntities[i]->getCollisionRect();
		rect(aBuffer, mCamera->getOffset().x + r.myTopLeft.x, mCamera->getOffset().y + r.myTopLeft.y, mCamera->getOffset().x + r.myBottomRight.x, mCamera->getOffset().y + r.myBottomRight.y, 0xff0000);
	}
	*/
}

void 
Room::privDrawLayer( BITMAP* aBuffer, Layer* aLayer )
{
	float2 clampTopLeft(
		-getCamera()->getOffset().x/getTileWidth(),
		-getCamera()->getOffset().y/getTileHeight());

	if (clampTopLeft.x < 0)
	{
		clampTopLeft.x = 0;
	}
	if (clampTopLeft.y < 0)
	{
		clampTopLeft.y = 0;
	}

	float2 clampBottomRight(
		(aBuffer->w-getCamera()->getOffset().x)/getTileWidth(), 
		(aBuffer->h-getCamera()->getOffset().y)/getTileHeight());

	if (clampBottomRight.x > aLayer->getWidth())
	{
		clampBottomRight.x = aLayer->getWidth();
	}
	if (clampBottomRight.y > aLayer->getHeight())
	{
		clampBottomRight.y = aLayer->getHeight();
	}

	int offsetx = getCamera()->getOffset().x;
	int offsety = getCamera()->getOffset().y;

	for (int x = clampTopLeft.x; x < clampBottomRight.x; ++x) 
	{
		for (int y = clampTopLeft.y; y < clampBottomRight.y; ++y) 
		{		
			privDrawTile(
				aBuffer,
				offsetx,
				offsety, 
				aLayer->getTile(x, y),
				x, 
				y);
		}
	}
}

void 
Room::privDrawTile( 
   BITMAP*	aBuffer,
   int		aOffsetX,
   int		aOffsetY,
   Tile&	aTile,
   int		aTileX,
   int		aTileY)
{
	aTile.onDraw(aBuffer, aOffsetX + aTileX*aTile.getWidth(), aOffsetY + aTileY*aTile.getHeight());
}

bool 
Room::isCollidable( 
	int		aX, 
	int		aY)
{
	return mTileLayer->getTile(aX, aY).getCollide();
}

bool Room::isDangerous(int aX, int aY)
{
	return mTileLayer->getTile(aX, aY).getDangerous();
}

void Room::setCollidable(int aX, int aY, bool aCollide)
{
	mTileLayer->getTile(aX, aY).setCollide(aCollide);
}

bool Room::rayCast(float2 origin, float2 direction, bool cullBeyondDirection, int &tileXOut, int &tileYOut)
{
	if (floatIsZero(direction))
	{
		return false;
	}

	int ix = (int)floor(origin.x) / getTileWidth();
	int iy = (int)floor(origin.y) / getTileHeight();
	float dx = (origin.x / getTileWidth() - ix);
	float dy = (origin.y / getTileHeight() - iy);
	float tx = direction.x > 0 ? 1 : 0;
	float ty = direction.y > 0 ? 1 : 0;

	int minX = 0;
	int maxX = getWidthInTiles();
	int minY = 0;
	int maxY = getHeightInTiles();
	if ( cullBeyondDirection ) {
		minX = math3d::max(minX, ix + (int)(math3d::min(0.0f, direction.x) / getTileWidth() - 1.0f));
		maxX = math3d::min(maxX, ix + (int)(math3d::max(0.0f, direction.x) / getTileWidth() + 2.0f));
		minY = math3d::max(minY, iy + (int)(math3d::min(0.0f, direction.y) / getTileHeight() - 1.0f));
		maxY = math3d::min(maxY, iy + (int)(math3d::max(0.0f, direction.y) / getTileHeight() + 2.0f));
	}
	bool hit = false;
	while (ix >= minX && ix < maxX && iy >= minY && iy < maxY )
	{
		if ( isCollidable(ix, iy) ) {
			hit = true;
			break;
		}

		if ( direction.y == 0 || (direction.x != 0 && ((tx-dx)/direction.x < (ty-dy) / direction.y)) )
		{
			dy += direction.y * (tx - dx) / direction.x;
			if ( direction.x > 0 )
			{
				ix++;
				dx = 0;
			} else {
				ix--;
				dx = 1;
			}
		} else {
			dx += direction.x * (ty - dy) / direction.y;
			if ( direction.y > 0 )
			{
				iy++;
				dy = 0;
			} else {
				iy--;
				dy = 1;
			}
		}
	}
	if ( hit ) {
		tileXOut = ix;
		tileYOut = iy;
		float2 tileCenter(ix * getTileWidth() + getTileWidth() / 2, iy * getTileHeight() + getTileHeight() / 2);
		if ( cullBeyondDirection && lengthCompare(origin - tileCenter, direction) > 0 ) {
			return false;
		}
		return true;
	} else {
		return false;
	}
}	

int Room::getTileHeight()
{
	return 10;
}

int Room::getTileWidth()
{
	return 10;
}

int Room::getWidthInTiles()
{
	return mTileLayer->getWidth();
}

int Room::getHeightInTiles()
{
	return mTileLayer->getHeight();
}

int Room::getWidthInPixels()
{
	return getWidthInTiles() * getTileWidth();
}

int Room::getHeightInPixels()
{
	return getHeightInTiles() * getTileHeight();
}

int Room::getWorldOffsetX()
{
	return myWorldOffsetX;
}

int Room::getWorldOffsetY()
{
	return myWorldOffsetY;
}

void Room::onLogic() 
{
	myFrameCounter++;

	if (myIsCompleted && myFrameCounter == 60)
		Music::playSong("data/music/level_completed.xm");

	if (mHero->isDead() && !myHeroIsDead)
	{
		myFrameCounter = 0;
		myHeroIsDead = true;
		return;
	}

	if (mHero->isDead() && myFrameCounter > 120)
	{
		myWorld->respawn(true);
		return;
	}

	if (mHero->isDead())
	{
		return;
	}

	for (int i = 0; i < (int)mEntities.size(); i++)
	{
		if (mEntities[i]->isRemoved())
		{
/*			if (mEntities[i]->isDamagable())
			{
				for (unsigned int j = 0; j < mDamagableEntities.size(); j++)
				{
					if (mDamagableEntities[j] == mEntities[i])
					{
						mDamagableEntities.erase(mDamagableEntities.begin() + j);
						break;
					}
				}
			}

			if (mEntities[i]->isHookable())
			{
				for (unsigned int j = 0; j < mHookableEntities.size(); j++)
				{
					if (mHookableEntities[j] == mEntities[i])
					{
						mHookableEntities.erase(mHookableEntities.begin() + j);
						break;
					}
				}
			}*/

			delete mEntities[i];
			mEntities.erase(mEntities.begin()+i);
			i--;
		}
	}

	for (int i = 0; i < (int)mEntities.size(); i++)
	{
		if (mHero->isDead())
			break;

		if (mEntities[i] != mHero)
			mEntities[i]->update();
	}

	mHero->update();

	for (int i = 0; i < (int)mEntities.size(); i++)
	{
		Entity* entity = mEntities[i];
		if (entity->getPosition().x - entity->getHalfSize().x > getWidthInPixels() ||
			entity->getPosition().y - entity->getHalfSize().y > getHeightInPixels() ||
			entity->getPosition().x + entity->getHalfSize().x < 0 ||
			entity->getPosition().y + entity->getHalfSize().y < 0)
		{
			if (entity == mHero)
			{
				myWorld->loadRoom(mHero->getPosition() + float2(myWorldOffsetX * getTileWidth(), myWorldOffsetY * getTileWidth()));
			}
			else
			{
				entity->remove();
			}
		}

	}

	getCamera()->onLogic(getHero(), float2(0.0f, 0.0f), float2(getWidthInTiles() * getTileWidth(), getHeightInTiles() * getTileHeight()));
}

void Room::addEntity(Entity *aEntity)
{
	Hero *hero = dynamic_cast<Hero *>(aEntity);
	if (hero != 0)
	{
		mHero = hero;
	}
	aEntity->setRoom(this);
	mEntities.push_back(aEntity);

	/*if (aEntity->isDamagable())
		mDamagableEntities.push_back(aEntity);

	if (aEntity->isHookable())
		mHookableEntities.push_back(aEntity);*/
}

Hero *Room::getHero()
{	
	return mHero;
}


void Room::removeHero()
{
	mEntities.erase(std::find(mEntities.begin(), mEntities.end(), mHero));
	mHero = 0;
}

Camera* 
Room::getCamera()
{
	return mCamera;
}

void Room::setCamera( Camera* aCamera )
{
	mCamera = aCamera;
}

std::vector<Entity*> Room::checkEntitiesForCollision(Entity* checkAgainstThis){
	std::vector<Entity*> entities;
	for(int i=0; i<mEntities.size();i++){
		
		if(!mEntities[i]->isShootable()){
			continue;
		}
		Entity::CollisionRect cr= mEntities[i]->getCollisionRect();
		if(Entity::Collides(checkAgainstThis->getCollisionRect(),cr)){
			entities.push_back(mEntities[i]);
		}
	}
	return entities;
}

std::vector<Entity*> Room::getSolidEntities() {
	std::vector<Entity*> entities;
	for(int i=0; i<mEntities.size();i++){
		if(mEntities[i]->isSolid()){
			entities.push_back(mEntities[i]);
		}
	}
	return entities;
}

std::vector<Entity*> Room::getEnemies() {
	std::vector<Entity*> entities;
	for(int i=0; i<mEntities.size();i++){
		if(mEntities[i]->isEnemy()){
			entities.push_back(mEntities[i]);
		}
	}
	return entities;
}

void Room::endGame() {
	myWorld->endGame();
}