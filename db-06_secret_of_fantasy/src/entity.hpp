#ifndef DBSH07_ENTITY_HPP
#define DBSH07_ENTITY_HPP

#include <allegro.h>

#include <string>

class Room;

class Entity
{
public:
	enum Direction
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	enum Type
	{
		PLAYER,
		ENEMY,
		OTHER,
		EXPLODABLE,
		DIGABLE
	};

	Entity(Type type, bool collidable, int level = 0);
    Entity(Type type, int x, int y, int w, int h, bool collidable, int level = 0);
	virtual ~Entity() { };

	virtual void setSize(int w, int h);

	virtual void setPosition(int x, int y);

	virtual void setRoom(Room* room) { mRoom = room; };

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

	virtual int getBottomY();

	virtual bool collidesWith(Entity *other, int padding);

	virtual void draw(BITMAP *dest, int scrollx, int scrolly) = 0;

	virtual void drawForeground(BITMAP *dest, int scrollx, int scrolly) {};

	virtual void logic() = 0;

    virtual bool isToBeDeleted() { return false; }

	virtual bool isCollidable();

    virtual void message(const std::string& message, Entity* distributor) {}

	virtual void handleCollision(Entity *other);

	virtual void damage(int damage, Direction direction) {}

	int getLevel() {return mLevel;};

	int getXCenterInTile(int x);
	int getYCenterInTile(int y);
	int getYBottomInTile(int y);
	int getXInTile(int x);
	int getYInTile(int y);
	int getDistance(Entity* other);

	int getMaxHealth() { return mMaxHealth; }
	void setMaxHealth(int health);
	int getHealth() { return mHealth; }
	void setHealth(int health);
	Type getType() { return mType; }
protected:
	Type mType;
	int mX, mY, mW, mH, mHealth, mMaxHealth;
	bool mCollidable;
	bool mKillsPlayer;
	Room* mRoom;
	int mLevel;
};
#endif