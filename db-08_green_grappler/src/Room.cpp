#include "Room.hpp"
#include "Resource.hpp"
#include "Entity.hpp"
#include "Hero.hpp"
#include "Layer.hpp"
#include "Tile.hpp"
#include "Camera.hpp"
#include "Coin.hpp"
#include "Font.hpp"
#include "Input.hpp"
#include "Music.hpp"
#include "ParticleSystem.hpp"

#include <stdio.h>

using namespace std;


Room::Room(Layer* aBackgroundLayer,		  
		   Layer* aMiddleLayer,		   
		   Layer* aForegroundLayer)
	: mBackgroundLayer(aBackgroundLayer)
	, mMiddleLayer(aMiddleLayer)
	, mForegroundLayer(aForegroundLayer)
	, mHero(0)
	, myHeroIsDead(false)
	, myIsCompleted(false)
{
	myFont = Resource::getFont("data/images/font.bmp");
}

Room::~Room() {
	delete mBackgroundLayer;
	delete mMiddleLayer;
	delete mForegroundLayer;
}

void Room::onDraw( BITMAP* aBuffer )
{
	if (mHero->isDead())
	{
		if (myFrameCounter == 0 || myFrameCounter == 5 || myFrameCounter == 10)
			rectfill(aBuffer, 0, 0, 320, 240, makecol(231,215,156));
		else
			rectfill(aBuffer, 0, 0, 320, 240, makecol(57,56,41));
		
		if (myFrameCounter < 60)
			mHero->draw(aBuffer, mCamera->getOffset().x, mCamera->getOffset().y, 0);
		return;
	}


	privDrawLayer(aBuffer, mBackgroundLayer);
	privDrawLayer(aBuffer, mMiddleLayer);

	for (int layer  = 0; layer < 5; layer++)
	{
		for (int i = 0; i < (int)mEntities.size(); i++)
		{
			if (mEntities[i]->getLayer() != layer)
				continue;

			mEntities[i]->draw(aBuffer, mCamera->getOffset().x, mCamera->getOffset().y, 0);
		}
	}

	privDrawLayer(aBuffer, mForegroundLayer);

	if (myIsCompleted)
	{
		myFont->drawCenter(aBuffer, "LEVEL COMPLETED!", 0, 0, 320, 240);
	}
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
	return mMiddleLayer->getTile(aX, aY).getCollide();
}

bool 
Room::isHookable(
				int		aX,
				int		aY	)
{
	return mMiddleLayer->getTile(aX, aY).getHook();
}

void Room::setHookable(int aX, int aY, bool aHookable)
{
	mMiddleLayer->getTile(aX, aY).setHook(aHookable);
}

void Room::setCollidable(int aX, int aY, bool aCollide)
{
	mMiddleLayer->getTile(aX, aY).setCollide(aCollide);
}

bool Room::destroyTile(int aX, int aY)
{
	bool spawnDebris = mMiddleLayer->getTile(aX, aY).getCollide();
	mMiddleLayer->getTile(aX, aY) = Tile();  // Hooray for references
	mForegroundLayer->getTile(aX, aY) = Tile();
	if (spawnDebris) {
		ParticleSystem* ps = new ParticleSystem(Resource::getAnimation("data/images/debris.bmp", 4), 20, 100, 20, 1, 50, 3, float2(0.0f, -50.0f), 5.0f);
		ps->setPosition(float2(aX * getTileWidth() + getTileWidth() * 0.75f, aY * getTileHeight() + getTileHeight() * 0.75f));
		addEntity(ps);
	}
	return spawnDebris;
}

bool 
Room::damageDone( int aX, int aY )
{
	Entity::CollisionRect rect;
	rect.myTopLeft = float2(aX, aY);
	rect.myBottomRight = float2(aX, aY) + float2(1, 1);

	for (unsigned int i = 0; i < mDamagableEntities.size(); i++)
	{
		Entity* entity = mDamagableEntities[i];
		if (Entity::Collides(rect, entity->getCollisionRect()))
		{
			entity->onDamage();
			return true;
		}
	}

	return false;
}

Entity *Room::findHookableEntity(float2 position)
{
	for (unsigned int i = 0; i < mHookableEntities.size(); i++)
	{
		Entity *entity = mHookableEntities[i];
		float2 toEntity = entity->getPosition() - position;
		if (abs(toEntity.x) < entity->getHalfSize().x && abs(toEntity.y) < entity->getHalfSize().y) {
			return entity;
		}
	}

	return 0;
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
	return 10;//mMiddleLayer.ge();
}

int Room::getTileWidth()
{
	return 10;//mMap.GetTileWidth();
}

int Room::getWidthInTiles()
{
	return mMiddleLayer->getWidth();
}

int Room::getHeightInTiles()
{
	return mMiddleLayer->getHeight();
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
		mHero->respawn();
		for (unsigned int i = 0; i < mEntities.size(); i++)
		{
			mEntities[i]->onRespawn();
		}

		getCamera()->centerToHero(mHero);
		getCamera()->onRespawn();
		myHeroIsDead = false;
		
	}

	if (mHero->isDead())
	{
		return;
	}

	for (int i = 0; i < (int)mEntities.size(); i++)
	{
		if (mEntities[i]->isRemoved())
		{
			if (mEntities[i]->isDamagable())
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
			}

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
		if (entity->getPosition().x - entity->getHalfSize().x > getWidthInTiles()*getTileWidth() ||
			entity->getPosition().y - entity->getHalfSize().y > getHeightInTiles()*getTileHeight() ||
			entity->getPosition().x + entity->getHalfSize().x < 0 ||
			entity->getPosition().y + entity->getHalfSize().y < 0)
		{			
			entity->remove();
		}

	}

	getCamera()->onLogic(getHero(), mCameraTopLeft, mCameraBottomRight);
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

	if (aEntity->isDamagable())
		mDamagableEntities.push_back(aEntity);

	if (aEntity->isHookable())
		mHookableEntities.push_back(aEntity);
}

Hero *Room::getHero()
{	
	return mHero;
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

void Room::setCameraRect( float2 aTopLeft, float2 aBottomRight )
{
	mCameraTopLeft = aTopLeft;
	mCameraBottomRight = aBottomRight;
}

std::vector<Entity*>& Room::getDamagableEntities()
{
	return mDamagableEntities;
}

std::vector<Entity*>& Room::getHookableEntities()
{
	return mHookableEntities;
}

void Room::broadcastButtonDown( int aId )
{
	for (unsigned int i = 0; i < mEntities.size(); i++)
		mEntities[i]->onButtonDown(aId);
}



void Room::broadcastButtonUp( int aId )
{
	for (unsigned int i = 0; i < mEntities.size(); i++)
		mEntities[i]->onButtonUp(aId);

}

void Room::broadcastStartWallOfDeath()
{
	for (unsigned int i = 0; i < mEntities.size(); i++)
		mEntities[i]->onStartWallOfDeath();
}

bool Room::isCompleted()
{
	if (myIsCompleted && myFrameCounter > 60 * 4)
	{
		Music::stop();
		Input::enable();
		return true;
	}

	return false;
}

void Room::setCompleted()
{
	for (unsigned int i = 0; i < mEntities.size(); i++)
		mEntities[i]->onLevelComplete();


	myFrameCounter = 0;
	myIsCompleted = true;
	mHero->imortal();
	Input::disable();
	Music::stop();
}

void Room::createTileBackup()
{
	mBackgroundLayerBackup = *mBackgroundLayer;
	mMiddleLayerBackup = *mMiddleLayer;
	mForegroundLayerBackup = *mForegroundLayer;
}

void Room::restoreTileBackup()
{
	delete mBackgroundLayer;
	delete mMiddleLayer;
	delete mForegroundLayer;
	mBackgroundLayer = new Layer(mBackgroundLayerBackup);
	mMiddleLayer = new Layer(mMiddleLayerBackup);
	mForegroundLayer = new Layer(mForegroundLayerBackup);
}

void Room::broadcastBoosFloorActivate()
{
	for (unsigned int i = 0; i < mEntities.size(); i++)
		mEntities[i]->onBossFloorActivate();
}

void Room::broadcastBoosWallActivate()
{
	for (unsigned int i = 0; i < mEntities.size(); i++)
		mEntities[i]->onBossWallActivate();
}

void Room::broadcastBoosWallDectivate()
{
	for (unsigned int i = 0; i < mEntities.size(); i++)
		mEntities[i]->onBossWallDeactivate();
}
