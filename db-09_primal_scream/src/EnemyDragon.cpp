#include "Precompiled.hpp"

#include "Resource.hpp"
#include "Room.hpp"
#include "EnemyDragon.hpp"
#include "Hero.hpp"
#include "Sound.hpp"

EnemyDragon::EnemyDragon(bool isWalking, float2 speed) 
		: mInitialHp(200)
		, mCurrentHp(200)
		, mFacingDirection(Direction_Left)
		, mWalkAnimation("data/images/dragon_walk.bmp",4)
		, mFlyAnimation("data/images/dragon_fly.bmp",4)
		, mBlinkingTicksLeft(0)
		, mFrame(0)
		, mGravityHitTimer(0)
		, mLastTurnTick(0)
		, mCurrentTick(0)
		, mDeathFrame(0)
		, mShootable(true)
		, mWalking(isWalking)
		, myDrawHit(false)
{
	setSize(float2(15.f,18.f));
	mDeathAnimation= Resource::getAnimation("data/images/death.bmp",4);
	mGravityAnimation= Resource::getAnimation("data/images/gravitybubble.bmp",4);
	mSpeed=speed;
}
EnemyDragon::~EnemyDragon(){
}

void EnemyDragon::setWalking(bool walks){
	mInitialHp=100;
	mCurrentHp=100;
	mWalking = walks;
	mSpeed=float2(30.0f,40.f);
}
void EnemyDragon::draw(BITMAP *buffer, int offsetX, int offsetY, int layer){
	int x = getDrawPositionX();
	int y = getDrawPositionY();
	int frame = 1;
	if (mCurrentHp<=0)
	{
		frame = mDeathFrame/5;
		mDeathAnimation->drawFrame(buffer,
			frame, 
			offsetX + x - mDeathAnimation->getFrameWidth()/2, 
			offsetY + y+getHalfSize().y-mDeathAnimation->getFrameHeight());
		return;
	}	
	frame = mFrame/4;

	Blending blending = Blending_None;

	if (myDrawHit)
	{
		blending = Blending_Lighten;
		myDrawHit = false;
	}

	if ((mBlinkingTicksLeft/6)%2 == 0)
	{
		bool gravityFlip = getGravityDirection() < 0;

		if (mWalking){
			if(gravityFlip){
				int gFrame = mFrame/8;
				mGravityAnimation->drawFrame(buffer,
				gFrame, 
				offsetX + x - mGravityAnimation->getFrameWidth() / 2, 
				offsetY + y - mGravityAnimation->getFrameHeight() / 2, false, false, blending);
			}

			mWalkAnimation.drawFrame(buffer,
				frame, 
				offsetX + x - mWalkAnimation.getFrameWidth() / 2, 
				offsetY + y + (gravityFlip ? -getHalfSize().y : getHalfSize().y - mWalkAnimation.getFrameHeight()),
				mFacingDirection == Direction_Right,gravityFlip, blending);
		} else {
			mFlyAnimation.drawFrame(buffer,
				frame, 
				offsetX + x - mFlyAnimation.getFrameWidth() / 2, 
				offsetY + y + getHalfSize().y - mFlyAnimation.getFrameHeight(),
				mFacingDirection == Direction_Right, false, blending);
		}
	}
}
void EnemyDragon::update(){
	mCurrentTick++;

	if(! mWalking) {
		if (mCurrentTick % 45 == 0){
			// it will reset every 45, i.e., we don't use normal delay for this
			toggleGravityDirection(500);
		}
	}
	if(mCurrentHp <= 0) {
		mShootable=false;
		mDeathFrame++;
		if (mDeathFrame >= 20){
			remove();
		}
		return;
	}

	if (mGravityHitTimer <= 0){
		mGravityDirection=1;
	} else {
		mGravityHitTimer--;
	}
	// walk
	int cur_x = getPosition().x;
	int cur_y = getPosition().y;
	int floor_y, edge_x;
	int bumps;
	// Turn around
	floor_y= cur_y+(getHalfSize().y+1)*mGravityDirection;
	if (mFacingDirection == Direction_Left){
		edge_x=cur_x-getHalfSize().x-1;
	} else {
		edge_x=cur_x+getHalfSize().x+1;
	}

	if(mWalking){
		if(mCurrentTick-mLastTurnTick > 60){
			if(! getRoom()->isCollidable(edge_x/10,floor_y/10)){
				toggleDirection();
				mLastTurnTick=mCurrentTick;
			} 
		}
		if(mCurrentTick-mLastTurnTick < 60){
			setVelocity(float2(.0f,mSpeed.y*getGravityDirection()));
		} else {
			setVelocity(float2(mSpeed.x*getDirection(),mSpeed.y*getGravityDirection()));
		}
		//setVelocity(float2(12.0f,.0f));
		bumps=moveWithCollision();
	
		if((bumps & Direction_Left) != 0 || (bumps & Direction_Right) != 0){
			toggleDirection();
			mLastTurnTick=mCurrentTick;
		}
		if (getRoom()->isCollidable(edge_x/10,floor_y/10)){
			mLastTurnTick-=60;
		}
	} else {
		setVelocity(float2(mSpeed.x*getDirection(),mSpeed.y*getGravityDirection()));
				bumps=moveWithCollision();
	
		if((bumps & Direction_Left) != 0 || (bumps & Direction_Right) != 0){
			toggleDirection();
			mLastTurnTick=mCurrentTick;
		}
	}
	mFrame ++;
	
	if (mBlinkingTicksLeft)
	{
		mBlinkingTicksLeft --;
	}

	if (touchesDangerousTile())
	{
		hit(10);
	}
	Entity::CollisionRect cr = getRoom()->getHero()->getCollisionRect();
	if (mCurrentHp > 0 && Collides(getCollisionRect(), cr))
	{
		getRoom()->getHero()->die();
	}
}
int EnemyDragon::getHp(){return mCurrentHp;}
void EnemyDragon::hit(int damage){
	if (mCurrentHp > 0)
	{
		myDrawHit = true;
		mCurrentHp-=damage;

		if (mCurrentHp <= 0)
		{
			Sound::playSample("data/sounds/dragondeath.wav");
		}
	}

}
int EnemyDragon::getLayer(){return 1;}
void EnemyDragon::toggleDirection(){mFacingDirection=(mFacingDirection==Direction_Left)?Direction_Right:Direction_Left;}
int EnemyDragon::getDirection(){return (mFacingDirection == Direction_Left)?-1:1;}

void EnemyDragon::toggleGravityDirection(int timer){
	mGravityDirection*=-1;
	mGravityHitTimer=timer;
}
