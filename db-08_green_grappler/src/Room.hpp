#pragma once

#include "Layer.hpp"

class Tile;
class Entity;
class Hero;
class Camera;
class Font;

class Room
{
public:
	Room(
		Layer* aBackgroundLayer,
		Layer* aMiddleLayer,
		Layer* aForegroundLayer);

	~Room();

	void onLogic();
	void onDraw(BITMAP* aBuffer);

	bool isCollidable(
			int		aX,
			int		aY	);

	bool isHookable(
		int		aX,
		int		aY	);

	void setHookable(int aX, int aY, bool aHookable);
	void setCollidable(int aX, int aY, bool aCollide);
	bool destroyTile(int aX, int aY);

	bool damageDone(
		int		aX,
		int		aY	);

	Entity *findHookableEntity(float2 position);

	bool rayCast(float2 origin, float2 direction, bool cullBeyondDirection, int &tileXOut, int &tileYOut);

	std::vector<Entity*>& getDamagableEntities();
	std::vector<Entity*>& getHookableEntities();

	int	 getTileHeight();
	int	 getTileWidth();
	int  getWidthInTiles();
	int  getHeightInTiles();

	void addEntity(Entity *aEntity);

	void setCamera(Camera* aCamera);
	void setCameraRect(float2 aTopLeft, float2 aBottomRight);

	void broadcastButtonDown(int aId);
	void broadcastButtonUp(int aId);
	void broadcastStartWallOfDeath();
	void broadcastBoosFloorActivate();
	void broadcastBoosWallActivate();
	void broadcastBoosWallDectivate();

	Hero *getHero();

	Camera* getCamera();

	bool isCompleted();

	void setCompleted();

	void createTileBackup();
	void restoreTileBackup();

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

	Layer* mBackgroundLayer;
	Layer* mMiddleLayer;
	Layer* mForegroundLayer;
	Layer mBackgroundLayerBackup;
	Layer mMiddleLayerBackup;
	Layer mForegroundLayerBackup;
	bool *mHookable;

	std::vector<Entity*> mEntities;
	std::vector<Entity*> mDamagableEntities;
	std::vector<Entity*> mHookableEntities;

	Camera* mCamera;
	float2  mCameraTopLeft;
	float2  mCameraBottomRight;

	Hero* mHero;
	int myFrameCounter;
	bool myHeroIsDead;
	bool myIsCompleted;
	Font* myFont;
};
