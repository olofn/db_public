#ifndef DBSH07_BULLET_HPP
#define DBSH07_BULLET_HPP
#include <string>

#include "entity.hpp"

class Bullet: public Entity
{
public:
    Bullet(int x, int y, int w, int h, unsigned int type, float dx, float dy, const std::string& filename, int damage);
    unsigned int getType() { return mType; }
	void logic(Level* level);
	void draw(BITMAP *dest, int scrolly, unsigned int layer);
    bool drawInLayer(unsigned int layer) { return layer == Entity::PLAYER_LAYER; }
	void handleCollision(Entity *other, Level *level);
	bool isToBeDeleted();
	virtual int getDamage() { return mDamage; };

protected:
    unsigned int mType;
	float mDx;
	float mDy;
	float mX, mY;
	int mDamage;
	bool mIsToBeDeleted;
};

#endif