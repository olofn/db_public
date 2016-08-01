#ifndef DB_SHOT_HPP
#define DB_SHOT_HPP

#include "entity.hpp"
#include "animation.hpp"

class Shot : public Entity
{
public:
	Shot(Entity::Type type,
		 Entity::Type killType,
		 int x, 
		 int y, 
		 int dx, 
		 int dy, 
		 int framesToLive, 
		 const std::string& animation,
		 int animationFrames,
		 int damage,
		 Entity::Direction direction);
	void logic();
	void draw(BITMAP *dest, int scrollx, int scrolly){}
	void drawForeground(BITMAP *dest, int scrollx, int scrolly);
	bool isToBeDeleted();

protected:
	int mFramesToLive;
	Animation mAnimation;
	int mDX;
	int mDY;
	Entity::Type mKillType;
	int mDamage;
	bool mDamagePerformed;
	Entity::Direction mDirection;
};

#endif