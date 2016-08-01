#ifndef DB_ITEMENTITY_HPP
#define DB_ITEMENTITY_HPP
#include <vector>
#include "item.hpp"
#include "entity.hpp"
#include "animation.hpp"

class ItemEntity: public Entity
{
public:
	ItemEntity(Animation* animation, int x, int y, bool bounceAway, int coins, int hearts);
	void logic();
	void draw(BITMAP *dest, int scrollx, int scrolly);
	void drawForeground(BITMAP *dest, int scrollx, int scrolly) {};
	int getCoins();
	bool isToBeDeleted();
	~ItemEntity();
private:
	Animation* mAnimation;
	float mSpeed, mDirection, mXasFloat, mYasFloat, mBounceOffset, mBounceSpeed;
	int mCoins;
	int mHearts;
	bool mIsToBeDeleted;
	int mTimeLeftToLive;
	SAMPLE *mSampleCoin;
	SAMPLE *mSampleHeart;
};
#endif