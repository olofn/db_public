#ifndef DB_CAMERA_HPP
#define DB_CAMERA_HPP

#include "entity.hpp"
#include "player.hpp"

#include "tilemap.hpp"

class Camera : public Entity
{
public:
	Camera();

	~Camera();

	virtual void setTarget(Player *player);

	virtual void moveToTarget(TileMap *tileMap);

	virtual void logic(Level *level);

	virtual void draw(BITMAP *dest, int scrollX, int scrollY, unsigned int layer);

	virtual bool isToBeDeleted();

    bool drawInLayer(unsigned int layer) { return false; }

protected:
	virtual void clampToMapEdges(TileMap *tileMap);

	Player *mPlayer;
};


#endif
