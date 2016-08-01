#pragma once

#include "Screen.hpp"
#include "Layer.hpp"

class Tile;
class Entity;
class Hero;
class Camera;
class Font;
class World;

class Room : public Screen
{
public:
	Room(Layer* aTiles, int aWorldOffsetX, int aWorldOffsetY);

	~Room();

	void setWorld(World *aWorld);
	void onLogic();
	void onDraw(BITMAP* aBuffer);

	bool isCollidable(int aX, int aY);
	bool isDangerous(int aX, int aY);

	std::vector<Entity*> checkEntitiesForCollision(Entity* checkAgainstThis);
	std::vector<Entity*> getSolidEntities();
	std::vector<Entity*> getEnemies();
	void setCollidable(int aX, int aY, bool aCollide);
	
	bool rayCast(float2 origin, float2 direction, bool cullBeyondDirection, int &tileXOut, int &tileYOut);

	int	 getTileHeight();
	int	 getTileWidth();
	int  getWidthInTiles();
	int  getHeightInTiles();
	int  getWidthInPixels();
	int  getHeightInPixels();
	int  getWorldOffsetX();
	int  getWorldOffsetY();

	void addEntity(Entity *aEntity);

	void setCamera(Camera* aCamera);

	void removeHero();

	Hero *getHero();

	Camera* getCamera();

	void endGame();

private:
	inline void privDrawTile(
			BITMAP* aBuffer,
			int		aOffsetX,
			int		aOffsetY,
			Tile&	aTile,
			int		aTileX,
			int		aTileY);

	void privDrawLayer( 
			BITMAP*	aBuffer, 
			Layer*	aLayer);

	Layer* mTileLayer;
	
	std::vector<Entity*> mEntities;
	
	Camera* mCamera;

	Hero* mHero;
	int myFrameCounter;
	bool myHeroIsDead;
	bool myIsCompleted;
	Font* myFont;
	World* myWorld;
	int myWorldOffsetX;
	int myWorldOffsetY;
};
