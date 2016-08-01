#ifndef DBSH07_MINE_HPP
#define DBSH07_MINE_HPP

#include "enemy.hpp"
#include "animation.hpp"

class Mine: public Enemy
{
public:
    Mine(int x, int y, bool isMagnetic);
    ~Mine();
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
	
	SAMPLE *mExplosionSample;
	SAMPLE *mBeepSample;
};

#endif