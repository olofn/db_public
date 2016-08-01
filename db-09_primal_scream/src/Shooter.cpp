#include "Precompiled.hpp"

#include "Room.hpp"
#include "Shooter.hpp"
#include "Resource.hpp"
#include "Hero.hpp"
#include "Sound.hpp"

Shooter::Shooter(float2 speed)
		: mHurtPlayer(true)
		,mFrame(0)
{
	mInitialVelocity[Shot::ShotType_Bullet] = float2(242.0f,0.f);
	mInitialVelocity[Shot::ShotType_GravityGrenade] = float2(.0f,-120.f);
	mInitialVelocity[Shot::ShotType_Fireball] = float2(.0f,-120.f);
	mSpeed=150;
	mFrame= rand();
}
Shooter::~Shooter(){
}

void Shooter::setCanHurtPlayer(bool hurtPlayer){
	mHurtPlayer=hurtPlayer;
}
void Shooter::setShotType(int _mShotType){
	mShotType = _mShotType;
}
int Shooter::getShotType(){
	return mShotType;
}

void Shooter::draw(BITMAP *buffer, int offsetX, int offsetY, int layer){
	return;
}

void Shooter::update(){
	//rand()
	if(mFrame %(mSpeed) == 0){
		Shot* ms = new Shot();
		ms->setShotType(Shot::ShotType_Fireball);
		ms->setInitialVelocity(float2(0.f,mInitialVelocity[Shot::ShotType_Fireball].y));
		ms->setPosition(getPosition());
		mRoom->addEntity(ms);
	}

	mFrame++;
}
void Shooter::setInitialVelocity(float2 velocity){
	mInitialVelocity[mShotType] = velocity;
}
float2 Shooter::getInitialVelocity()
{
	return mInitialVelocity[mShotType] ;
}

int Shooter::getLayer(){return 1;}