#include "Precompiled.hpp"

#include "Room.hpp"
#include "EnemyBoss.hpp"
#include "Shot.hpp"
#include "Hero.hpp"
#include "Util.hpp"
#include "Resource.hpp"
#include "Sound.hpp"

EnemyBoss::EnemyBoss() 
		: mInitialHp(2000)
		, mCurrentHp(2000)
		, mFacingDirection(Direction_Left)
		, mWalkAnimation("data/images/boss.bmp",5)
		, mBlinkingTicksLeft(0)
		, mFrame(0)
		, mGravityHitTimer(0)
		, mLastTurnTick(0)
		, mCurrentTick(0)
		, mDeathFrame(0)
		, myDrawHurt(false)
{
	setSize(float2(32.f,90.f));
	mDeathAnimation= Resource::getAnimation("data/images/death.bmp",4);
	mGravityAnimation= Resource::getAnimation("data/images/gravitybubble.bmp",4);
}
EnemyBoss::~EnemyBoss(){
}

void EnemyBoss::draw(BITMAP *buffer, int offsetX, int offsetY, int layer){
	int x = getDrawPositionX();
	int y = getDrawPositionY();
	int frame;
	if (mCurrentHp<=0)
	{
		frame = mDeathFrame/8;
		for(int i=0; i<8; i++){
			mDeathAnimation->drawFrame(buffer,
				frame, 
				offsetX + x - mDeathAnimation->getFrameWidth()/2 + ((frand()-0.5)*25.f), 
				offsetY + y+getHalfSize().y-mDeathAnimation->getFrameHeight()+((frand()-0.5)*50));
		}
		return;
	}
	frame = mFrame/60;

	if ((mBlinkingTicksLeft/6)%2 == 0)
	{
		Blending blending = Blending_None;

		if (myDrawHurt)
		{
			blending = Blending_Lighten;
			myDrawHurt = false;
		}

		bool gravityFlip = (getGravityDirection()>0)?false:true;

		if(gravityFlip){
			mGravityAnimation->drawFrame(buffer,
			frame, 
			offsetX + x - mGravityAnimation->getFrameWidth() / 2, 
			offsetY + y - mGravityAnimation->getFrameHeight() /2, false, false, blending);
		}

		float2 hpos = mRoom->getHero()->getPosition();

		mWalkAnimation.drawFrame(buffer,
			frame, 
			offsetX + x - mWalkAnimation.getFrameWidth() / 2, 
			offsetY + y + (gravityFlip ? -getHalfSize().y : getHalfSize().y - mWalkAnimation.getFrameHeight()),
			hpos.x > getPosition().x,
			gravityFlip, blending);
	}
}
void EnemyBoss::update(){
	mCurrentTick++;
	if(mCurrentHp <= 0){
		mDeathFrame++;
		if(mDeathFrame>128){
			remove();
			getRoom()->endGame();
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
	floor_y= cur_y+(getHalfSize().y+5)*mGravityDirection;
	if (mFacingDirection == Direction_Left){
		edge_x=cur_x-getHalfSize().x+3;
	} else {
		edge_x=cur_x+getHalfSize().x-3;
	}

	if(mCurrentTick-mLastTurnTick > 60){
		if(! getRoom()->isCollidable(edge_x/10,floor_y/10)){
			toggleDirection();
			mLastTurnTick=mCurrentTick;
		} 
	}
	if(mCurrentTick-mLastTurnTick < 60){
		setVelocity(float2(.0f,40.f*getGravityDirection()));
	} else {
		setVelocity(float2(12.0f*getDirection(),40.f*getGravityDirection()));
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
	mFrame ++;
	if (mFrame % 60 == 0){
		attack(Shot::ShotType_GravityGrenade);
	}
	if ((mFrame+25) % 60 == 0){
		attack(Shot::ShotType_Fireball);
	}
	if (mBlinkingTicksLeft)
	{
		mBlinkingTicksLeft --;
	}

	Entity::CollisionRect cr = getRoom()->getHero()->getCollisionRect();
	if (mCurrentHp > 0 && Collides(getCollisionRect(), cr))
	{
		getRoom()->getHero()->die();
	}
	if (touchesDangerousTile())
	{
		hit(50);
	}
}
int EnemyBoss::getHp(){return mCurrentHp;}
void EnemyBoss::hit(int damage){
	if (mCurrentHp > 0)
	{
		myDrawHurt = true;
		mCurrentHp-=damage;

		if (mCurrentHp <= 0)
		{
			Sound::playSample("data/sounds/bossdeath.wav");
		}
	}

}
int EnemyBoss::getLayer(){return 1;}
void EnemyBoss::toggleDirection(){mFacingDirection=(mFacingDirection==Direction_Left)?Direction_Right:Direction_Left;}
int EnemyBoss::getDirection(){return (mFacingDirection == Direction_Left)?-1:1;}

void EnemyBoss::toggleGravityDirection(int timer){
	mGravityDirection*=-1;
	mGravityHitTimer=timer;
}

void EnemyBoss::attack(int shotType){
	float2 hpos = mRoom->getHero()->getPosition();
	Direction dir((hpos.x-getPosition().x)<0?Direction_Left:Direction_Right);
	Shot* ms = new Shot();
	ms->setShotType(shotType);
	ms->setPosition(getPosition());
	ms->setDirection(dir);
	ms->setCanHurtPlayer(true);
	ms->setInitialVelocity(float2((frand()+0.5)*180.0f,(frand()-0.5f)*150));
	mRoom->addEntity(ms);
}

Direction EnemyBoss::getFacingDirection()
{
	return mFacingDirection;
}
