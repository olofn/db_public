#pragma once
#include "Entity.hpp"
#include "Animation.hpp"
#include "Shot.hpp"
//#include <vector>

class Shooter : public Entity{
public:
	Shooter(float2 speed);
	~Shooter();

	void update();
	void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
	void setShotType(int _mShotType);
	int getShotType();
	void setCanHurtPlayer(bool hurtPlayer);
	void setInitialVelocity(float2 velocity);
	float2 getInitialVelocity();
	int getLayer();
private:
	bool mHurtPlayer;
	int mShotType;
	int mFrame;
	int mSpeed;
	float2 mInitialVelocity[Shot::ShotType_Length];
};