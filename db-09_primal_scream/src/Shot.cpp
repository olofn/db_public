#include "Precompiled.hpp"

#include "Room.hpp"
#include "Shot.hpp"
#include "Resource.hpp"
#include "Hero.hpp"
#include "Sound.hpp"

Shot::Shot() 
		: mFacingDirection(Direction_Left)
		, mFrame(0)
		, cFrame(0)
		, mCollided(false)
		, mCollidedTimer(30)
		, mLife(0)
		, GRAVITY(4.f)
		, mHurtPlayer(false)
{
	mDamage[ShotType_Bullet] = 100;
	mDamage[ShotType_GravityGrenade] = 0;
	mDamage[ShotType_Fireball] = 200;
	mGravity[ShotType_Bullet] = false;
	mGravity[ShotType_GravityGrenade] = true;
	mGravity[ShotType_Fireball] = true;
	mToggleGravity[ShotType_Bullet] = false;
	mToggleGravity[ShotType_GravityGrenade] = true;
	mToggleGravity[ShotType_Fireball] = false;
	mDuration[ShotType_Bullet] = 2;
	mDuration[ShotType_GravityGrenade] = 4;
	mDuration[ShotType_Fireball] = 4;
	mGravityDuration[ShotType_Bullet] = 0;
	mGravityDuration[ShotType_GravityGrenade] = 5*60;
	mGravityDuration[ShotType_Fireball] = 0;
	mSize[ShotType_Bullet] = float2(5.f,3.f);
	mSize[ShotType_GravityGrenade] = float2(7.f,7.f);
	mSize[ShotType_Fireball] = float2(7.f,7.f);
	//mAcceleration[ShotType_Bullet];
	//mAcceleration[ShotType_GravityGrenade];
	mShotAnimation[ShotType_Bullet] = Resource::getAnimation("data/images/bullet.bmp",2);
	mShotAnimation[ShotType_GravityGrenade] = Resource::getAnimation("data/images/grenade.bmp",2);
	mShotAnimation[ShotType_Fireball] = Resource::getAnimation("data/images/fireball.bmp",2);
	mCollisionAnimation[ShotType_Bullet] = Resource::getAnimation("data/images/bullet_collision.bmp",2);
	mCollisionAnimation[ShotType_GravityGrenade] = Resource::getAnimation("data/images/grenade_collision.bmp",2);
	mCollisionAnimation[ShotType_Fireball] = Resource::getAnimation("data/images/grenade_collision.bmp",2);
	mShotType = ShotType_Bullet;
	
	mInitialVelocity[ShotType_Bullet] = float2(242.0f,0.f);
	mInitialVelocity[ShotType_GravityGrenade] = float2(200.0f,-80.f);
	mInitialVelocity[ShotType_Fireball] = float2(200.0f,0.f);
}
Shot::~Shot(){
}

void Shot::setCanHurtPlayer(bool hurtPlayer){
	mHurtPlayer=hurtPlayer;
}
void Shot::setShotType(int _mShotType){
	mShotType = _mShotType;
	setSize(mSize[mShotType]);
}
int Shot::getShotType(){
	return mShotType;
}


void Shot::draw(BITMAP *buffer, int offsetX, int offsetY, int layer){
	int x = getDrawPositionX();
	int y = getDrawPositionY();

	int frame;
	if(! hasCollided()){
		frame = mFrame/10;
		mShotAnimation[mShotType]->drawFrame(buffer,
			frame, 
			offsetX + x - mShotAnimation[mShotType]->getFrameWidth()/2, 
			offsetY + y+getHalfSize().y-mShotAnimation[mShotType]->getFrameHeight());
	} else {
		cFrame++;
		frame = cFrame/10;
		mCollisionAnimation[mShotType]->drawFrame(buffer,
			frame, 
			offsetX + x - mCollisionAnimation[mShotType]->getFrameWidth()/2, 
			offsetY + y+getHalfSize().y-mCollisionAnimation[mShotType]->getFrameHeight());
	}
}

bool Shot::hasCollided(){
	return mCollided;
}
void Shot::setCollided(bool _mCollided){
	mCollided = _mCollided;
}

void Shot::update(){
	if (++mLife > 180){
		setCollided(true);
	}
	if (touchesDangerousTile()){
		setCollided(true);
	}
	if(hasCollided()){
		if (--mCollidedTimer < 0){
			remove();
			//remove
		}
		return;
	}
	// move
	int cur_x = getPosition().x;
	int cur_y = getPosition().y;
	int floor_y, edge_x;
	int bumps;
	/*
	floor_y= cur_y+getHalfSize().y+5;
	if (mFacingDirection == Direction_Left){
		edge_x=cur_x-getHalfSize().x;
	} else {
		edge_x=cur_x+getHalfSize().x;
	}
	*/
	if(mGravity[mShotType] == ShotType_Bullet){
		setVelocity(float2(mInitialVelocity[mShotType].x*getDirection(),mInitialVelocity[mShotType].y));
	} else {
		setVelocity(float2(mInitialVelocity[mShotType].x*getDirection(),mInitialVelocity[mShotType].y+GRAVITY*mLife));
	}
	//setVelocity(float2(12.0f,.0f));
	bumps=moveWithCollision();

	if((bumps & Direction_Left) != 0 || (bumps & Direction_Right) != 0 || (bumps & Direction_Up) != 0|| (bumps & Direction_Down) != 0 ){
		setCollided(true);
		if (mShotType == ShotType_GravityGrenade || mShotType == ShotType_Fireball) { Sound::playSample("data/sounds/grenadeexplode.wav"); }
	}

	if(!mHurtPlayer){
		std::vector<Entity*> collidedEntity = mRoom->checkEntitiesForCollision(this);
		if(collidedEntity.size() > 0){
			setCollided(true);
			if (mShotType == ShotType_GravityGrenade || mShotType == ShotType_Fireball) { Sound::playSample("data/sounds/grenadeexplode.wav"); }
			for(int i=0;i<collidedEntity.size();i++){
				attack(collidedEntity[i]);
			}
		}
	} else {
		Hero* h = mRoom->getHero();
		Entity::CollisionRect cr= h->getCollisionRect();
		if(Collides(getCollisionRect(),cr)){
			setCollided(true);
			if (mShotType == ShotType_GravityGrenade || mShotType == ShotType_Fireball) { Sound::playSample("data/sounds/grenadeexplode.wav"); }
			if(mShotType == ShotType_Fireball || mShotType == ShotType_Bullet){
				h->die();
				return;
			}
			if(mShotType == ShotType_GravityGrenade){
				attack(h);
				return;
			}
		}
	}

	mFrame++;
	

}
void Shot::setInitialVelocity(float2 velocity){
	mInitialVelocity[mShotType] = velocity;
}
float2 Shot::getInitialVelocity()
{
	return mInitialVelocity[mShotType] ;
}
void Shot::attack(Entity* e){
	if(mToggleGravity[mShotType]){
		e->toggleGravityDirection(mGravityDuration[mShotType]);
	}
	e->hit(mDamage[mShotType]);
}
int Shot::getLayer(){return 1;}
void Shot::toggleDirection(){mFacingDirection=(mFacingDirection==Direction_Left)?Direction_Right:Direction_Left;}
void Shot::setDirection(int direction){ mFacingDirection=direction;}
int Shot::getDirection(){return (mFacingDirection == Direction_Left)?-1:1;}
