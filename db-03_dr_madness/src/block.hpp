#ifndef DBSH07_BLOCK_HPP
#define DBSH07_BLOCK_HPP

#include "entity.hpp"
#include "animation.hpp"

class Block: public Entity
{
public:
    Block(int x, int y, int width, int height, const std::string& filename, int hitCount, bool withOrb = false);
    ~Block();
    void logic(Level* level);
    void draw(BITMAP *dest, int scrolly, unsigned int layer);
    bool drawInLayer(unsigned int layer) { return layer == Entity::ENEMY_LAYER; }
    bool isToBeDeleted();
	void handleCollision(Entity *other, Level *level);
    unsigned int getType() { return Entity::BLOCK_TYPE; }

protected:
    Animation* mAnimation;
    bool mToBeDeleted;
    int mHitCount;
	bool mIsHit;
    int mFrameCounter;
	bool mWithOrb;
};

#endif