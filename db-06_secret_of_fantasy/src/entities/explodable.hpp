#ifndef DB_EXPLODABLE_HPP
#define DB_EXPLODABLE_HPP

#include "tilealignedentity.hpp"
#include "animation.hpp"

class Explodable: public TileAlignedEntity
{
public:
    Explodable(int x, int y);
    void draw(BITMAP *dest, int scrollx, int scrolly);
    void logic();
    bool isToBeDeleted();
	void damage(int damage, Entity::Direction direction);
protected:
    Animation mAnimation;
    bool mInitialized;
    bool mToBeDeleted;
private:
	std::string buildGameStateVariableString();
};
#endif