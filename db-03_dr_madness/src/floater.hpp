#ifndef DBSH07_FLOATER_HPP
#define DBSH07_FLOATER_HPP

#include "enemy.hpp"
#include "animation.hpp"

class Floater: public Enemy
{
public:
    Floater(int x, int y, int life);
    ~Floater();
    void logic(Level* level);
    void draw(BITMAP *dest, int scrolly, unsigned int layer);
    bool drawInLayer(unsigned int layer) { return layer == Entity::ENEMY_LAYER; }
    bool isToBeDeleted();
	void handleCollision(Entity *other, Level *level);
	unsigned int getType() { return Entity::ENEMY_TYPE; }

protected:
    Animation* mAnimation;
    bool mToBeDeleted;
	int mHitCount;
	bool mRenderAsHit;
	bool mIsMagnetic;
	float mDy, mDx;
	float mY, mX;
	int mFrameCount;
	float mRadius, mAngle;
	int mTargetX, mTargetY;
	
	SAMPLE *mExplosionSample;
};

#endif