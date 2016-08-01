#ifndef DBSH07_ENTITY_HPP
#define DBSH07_ENTITY_HPP

#include <allegro.h>

#include <string>

class Level;

class Entity
{
public:
	Entity(bool collidable);
    Entity(int x, int y, int w, int h, bool collidable);
	virtual ~Entity() { };

	virtual void setSize(int w, int h);

	virtual void setPosition(int x, int y);

	virtual int getX();

	virtual int getY();

	virtual int getWidth(); 

	virtual int getHeight();

	virtual void setX(int x);

	virtual void setY(int y);

	virtual void setWidth(int w); 

	virtual void setHeight(int h);

	virtual int getCenterX();

	virtual int getCenterY();

	virtual bool collidesWith(Entity *other);

	virtual void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer) = 0;

	virtual void logic(Level *level) = 0;

    virtual bool drawInLayer(unsigned int layer) = 0;

    virtual bool isToBeDeleted() { return false; }

	virtual bool isCollidable();

    virtual void message(const std::string& message, Entity* distributor) {}

	virtual void handleCollision(Entity *other, Level *level);

    static const int BACKGROUND_LAYER = 0;
    static const int PLAYER_LAYER = 1;
    static const int BEFORE_TILES_LAYER = 2;
    static const int AFTER_TILES_LAYER = 3;
    static const int FOREGROUND_LAYER = 4;
	static const int NUM_LAYERS = 5;

protected:
	int mX, mY, mW, mH;
	bool mCollidable;
	bool mKillsPlayer;
};
#endif
