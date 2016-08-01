#ifndef DBSH07_TURRET_HPP
#define DBSH07_TURRET_HPP

#include "enemy.hpp"
#include "animation.hpp"

class Turret: public Enemy
{
public:
	enum FireDirection
    {
		UP,
		DOWN,
        LEFT,
		RIGHT
    };

    Turret(int x, int y, FireDirection direction, int shots);
    ~Turret();
    void logic(Level* level);
    void draw(BITMAP *dest, int scrolly, unsigned int layer);
    bool drawInLayer(unsigned int layer) { return layer == Entity::ENEMY_LAYER; }
    bool isToBeDeleted();
	void handleCollision(Entity *other, Level *level);
	unsigned int getType() { return Entity::ENEMY_TYPE; }



protected:
    Animation* mAnimation;
	int mFrameCount;
	int mHitCount;
	bool mIsToBeDeleted;
	bool mRenderAsHit;
	FireDirection mDirection;
	int mShots;
	
};

#endif