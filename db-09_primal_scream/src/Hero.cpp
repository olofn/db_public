#include "Precompiled.hpp"

#include "Hero.hpp"
#include "Input.hpp"
#include "Constants.hpp"
#include "Room.hpp"
#include "Time.hpp"
#include "Animation.hpp"
#include "Sound.hpp"
#include "ParticleSystem.hpp"
#include "Resource.hpp"
#include "GameState.hpp"
#include "Camera.hpp"
#include "Shot.hpp"
#include "Portal.hpp"

static const float GROUND_ACCELERATION	= 15.0f;
static const float GROUND_DRAG			= 0.90f;
static const float GROUND_STOP_VELOCITY	= 4.5f;
static const float AIR_ACCELERATION		= 8.0f;
static const float AIR_DRAG				= 0.98f;
static const float JUMP_GRAVITY			= 5.0f;
static const float GRAVITY				= 10.0f;
static const float JUMP_VELOCITY		= 220.0f;
static const float HI_JUMP_VELOCITY		= 290.0f;
static const int   BLINKING_TICKS		= 100;
static const float KILL_VELOCITY		= 200.0f;
static const float MAX_X_VELOCITY		= 120.0f;
static const float MAX_Y_VELOCITY		= 200.0f;

Hero::Hero()
	: mOnGround(false)
	, mJumpHeld(false)
	, mJumpPrepressed(false)
	, mFrame(0)
	, mFacingDirection(Direction_Right)
	, mBlinkingTicksLeft(0)
	, mAnimationRun("data/images/hero_run.png", 4)
	, mAnimationJump("data/images/hero_jump.png", 1)
	, mAnimationFall("data/images/hero_fall.png", 1)
	, mAnimationHurt("data/images/hero_hurt.png", 1)
	, mSpawnPoint(-200,-200)
	, myIsDead(false)
	, myImortal(false)
	, mWeaponSelected(Weapon_None)
	, mGravityHitTimer(0)
	, mFramesSinceLandPlayed(0)
	, mySpawnPortal(false)
	, mySpawnPortalFrameCounter(0)
{
	mSize = float2(10.0f, 15.0f);
}

Hero::~Hero()
{
}

void Hero::update()
{
	if (mySpawnPortal)
	{
		mySpawnPortalFrameCounter++;
		if (mySpawnPortalFrameCounter == 1)
		{
			Portal* portal = new Portal();
			portal->setPosition(getPosition());
			getRoom()->addEntity(portal);
			return;
		}
		else if (mySpawnPortalFrameCounter >= 60 * 5)
		{
			mySpawnPortal = false;
		}
		else 
		{
			return;
		}
	}

	if (myIsDead)
		return;

	Entity::update();
	mFramesSinceLandPlayed++;

	if (mGravityHitTimer <= 0){
		mGravityDirection=1;
	} else {
		mGravityHitTimer--;
	}

	if (touchesDangerousTile())
	{
		die();
	}
	//checkEnemies();

	if (mSpawnPoint.x < -100 && mSpawnPoint.y < -100)
	{
		mSpawnPoint = getPosition();
	}

	float acceleration = mOnGround ? GROUND_ACCELERATION : AIR_ACCELERATION;
	
	if (Input::isHeld(Button_Left)) {
		mVelocity.x -= acceleration;
		mFacingDirection = Direction_Left;
	}

	if (Input::isHeld(Button_Right)) {
		mVelocity.x += acceleration;
		mFacingDirection = Direction_Right;
	}

	if(Input::isPressed(Button_Fire) && GameState::getInt(GameState::POWERUP_GRENADE) != 0){
		mWeaponSelected = Weapon_Gravity_Grenade;
		fireWeapon();
	}

	if(Input::isPressed(Button_ToggleWeapon) && GameState::getInt(GameState::POWERUP_GUN) != 0){
		mWeaponSelected = Weapon_Gun;
		fireWeapon();
	}

	mVelocity.x = clamp(mVelocity.x, -MAX_X_VELOCITY, MAX_X_VELOCITY);
	
	if (Input::isPressed(Button_Jump)) {
		mJumpPrepressed = true;
	}

	if (mOnGround && mJumpPrepressed) {
		Sound::playSample("data/sounds/jump.wav");
		mVelocity.y = GameState::getInt(GameState::POWERUP_HIJUMP) ? -HI_JUMP_VELOCITY : -JUMP_VELOCITY;
		mJumpHeld = true;
		mJumpPrepressed = false;
	}

	if (Input::isReleased(Button_Jump)) {
		if (mJumpHeld && mVelocity.y < 0) {
			mVelocity.y *= 0.5f;
		}

		mJumpHeld = false;
		mJumpPrepressed = false;
	}

	if (mVelocity.y >= 0) {
		mJumpHeld = false;
	}

	mMovementState = MovementState_Still;
	
	if (mOnGround) {
		if (abs(mVelocity.x) > GROUND_STOP_VELOCITY)
		{
			mMovementState = MovementState_Run;
		}
	}
	else
	{
		if (mVelocity.y < 0) {
			mMovementState = MovementState_Jump;
		} else {
			mMovementState = MovementState_Fall;
		}
	}
	
	if (mMovementState == MovementState_Still)
	{
		mVelocity.x = 0;
	}

	bool ground = moveOutOfSolidEntities();

	float2 usedVelocity(mVelocity.x, clamp(mVelocity.y, -MAX_Y_VELOCITY, MAX_Y_VELOCITY));
	unsigned int bumps = moveWithCollision(usedVelocity / Time::TicksPerSecond);
	
	if ((bumps & (Direction_Left | Direction_Right)) != 0) {
		mVelocity.x = 0;
	}

	if ((bumps & (Direction_Up | Direction_Down)) != 0) {
		mVelocity.y = 0;
	}

	float gravity = mJumpHeld ? JUMP_GRAVITY : GRAVITY;
	mVelocity.y += gravity * getGravityDirection();
	ground |= ((bumps & Direction_Down) != 0);
	if (ground && !mOnGround)
	{
		if (mFramesSinceLandPlayed > 6)
		{
			Sound::playSample("data/sounds/land.wav");
		}
		mFramesSinceLandPlayed = 0;
	}
	mOnGround = ground;

	float drag = mOnGround ? GROUND_DRAG : AIR_DRAG;
	mVelocity *= drag;

	mFrame ++;
	if (mBlinkingTicksLeft)
	{
		mBlinkingTicksLeft --;
	}
}

void Hero::draw(BITMAP *buffer, int offsetX, int offsetY, int layer)
{
	if (mySpawnPortal)
	{
		return;
	}

	int x = getDrawPositionX();
	int y = getDrawPositionY();

	if (myIsDead)
	{
		bool gravityFlip = (getGravityDirection()>0)?false:true;
		mAnimationHurt.drawFrame(buffer,
			0, 
			offsetX + x - mAnimationHurt.getFrameWidth()/2, 
			offsetY + y+getHalfSize().y-mAnimationHurt.getFrameHeight(),
			mFacingDirection == Direction_Left, gravityFlip);
		return;
	}

	Animation* animation = 0;
	int frame = 1;

//	mMovementState = MovementState_Jump;

	switch(mMovementState)
	{
	case MovementState_Run:
		animation = &mAnimationRun;
		frame = mFrame/5;
		break;
	case MovementState_Still:
		animation = &mAnimationRun;
		frame = 1;
		break;
	case MovementState_Jump:
		animation = &mAnimationJump;
		frame = 1;
		break;
	case MovementState_Fall:
		animation = &mAnimationFall;
		frame = 1;
		break;
	default:
		Entity::draw(buffer, offsetX, offsetY, layer);
	}

	if (mBlinkingTicksLeft > 0 && !mOnGround)
	{
		animation = &mAnimationHurt;
	}

	if ((mBlinkingTicksLeft/6)%2 == 0)
	{
		bool gravityFlip = (getGravityDirection()>0)?false:true;

		animation->drawFrame(buffer,
			frame, 
			offsetX + x - animation->getFrameWidth()/2, 
			offsetY + y + (gravityFlip ? -getHalfSize().y : getHalfSize().y - animation->getFrameHeight()),
			mFacingDirection == Direction_Left,
			gravityFlip);
	}
}

void Hero::kill()
{
	if (myImortal)
		return;

	if (!mBlinkingTicksLeft)
	{
		die();
	}
}

void Hero::die()
{
	myIsDead = true;
	Sound::playSample("data/sounds/start.wav");
}

void Hero::setLastSpawnPoint( float2 aPosition )
{
	mSpawnPoint = aPosition;
}

Direction Hero::getFacingDirection()
{
	return mFacingDirection;
}

void Hero::respawn()
{
	setPosition(mSpawnPoint);
	setVelocity(float2(0,0));
	myIsDead = false;
	mOnGround = false;
	mJumpHeld= false;
	mJumpPrepressed = false;
	mFrame = 0;
	mFacingDirection = Direction_Right;
	mBlinkingTicksLeft = 0;
}

bool Hero::isDead()
{
	return myIsDead;
}

void Hero::remove()
{
	die();
}

void Hero::imortal()
{
	myImortal = true;
}

void Hero::setRoom( Room *room )
{
	Entity::setRoom(room);

	mRoom->getCamera()->centerToHero(this);
}

void Hero::toggleWeapon() {
	bool foundWeapon=false;
	for(int i=0;i<Weapon_Length;i++){
		mWeaponSelected = ++mWeaponSelected % Weapon_Length;
		if(mWeaponSelected == Weapon_Gun){
			if(GameState::getInt(GameState::POWERUP_GUN)){
				foundWeapon=true;
				break;
			}
		}
		if(mWeaponSelected == Weapon_Gravity_Grenade){
			if(GameState::getInt(GameState::POWERUP_GRENADE)){
				foundWeapon=true;
				break;
			}
		}
	}
	if(! foundWeapon){
		mWeaponSelected = Weapon_None;
	}

}
void Hero::fireWeapon(){
	if(mWeaponSelected == Weapon_None){
		return;
	}
	Shot* ms = new Shot();
	if (mWeaponSelected == Weapon_Gun){
		ms->setShotType(Shot::ShotType_Bullet);
		Sound::playSample("data/sounds/shoot.wav");
	} else if (mWeaponSelected == Weapon_Gravity_Grenade){
		ms->setShotType(Shot::ShotType_GravityGrenade);
		Sound::playSample("data/sounds/throwgrenade.wav");
	}
	ms->setPosition(getPosition());
	ms->setDirection(getFacingDirection());
	ms->setInitialVelocity(float2(ms->getInitialVelocity().x, ms->getInitialVelocity().y * getGravityDirection()));
	mRoom->addEntity(ms);

}

void Hero::toggleGravityDirection(int timer){
	mGravityDirection*=-1;
	mGravityHitTimer=timer;
}
void Hero::checkEnemies(){
	std::vector<Entity*> entities;
	entities=mRoom->getEnemies();
	for (int i=0;i<entities.size();i++){
	  Entity::CollisionRect cr = entities[i]->getCollisionRect();
	  if(Collides(getCollisionRect(),cr)){
			die();
		}
	}
}

bool Hero::moveOutOfSolidEntities(){
	std::vector<Entity*> entities;
	entities = mRoom->getSolidEntities();
	bool ground = false;
	for(int i=0; i< entities.size();i++){
		float2 sepVec = getSeparationVector(getCollisionRect(),entities[i]->getCollisionRect());
		
		if(sepVec.y > 0.0f){
			mVelocity.y = max(entities[i]->getVelocity().y * 0.5f, mVelocity.y);
		}
		
		if(sepVec.y < 0.0f){
			mVelocity.y = min(entities[i]->getVelocity().y * 0.5f, mVelocity.y);
			ground=true;
		}

		if(sepVec.x > 0.0f){
			mVelocity.x = max(entities[i]->getVelocity().x * 0.5f, mVelocity.x);
		}

		if(sepVec.x < 0.0f){
			mVelocity.x = min(entities[i]->getVelocity().x * 0.5f, mVelocity.x);
		}

		setPosition(getPosition()+sepVec * 0.99f);
	}

	return ground;
}
float2 Hero::getSeparationVector(CollisionRect r1, CollisionRect r2){
	// Get X
	float r1x1 = r1.myTopLeft.x;
	float r1x2 = r1.myBottomRight.x;
	float r1w = r1x2-r1x1;
	float r1m1 = r1w/2 + r1x1;

	float r2x1 = r2.myTopLeft.x;
	float r2x2 = r2.myBottomRight.x;
	float r2w = r2x2-r2x1;
	float r2m1 = r2w/2 + r2x1;
	float xdirection = (r1m1-r2m1) > 0 ?1:-1;
	float xOverlap;

	// do we have overlap?
	if (abs(r1m1-r2m1) < (r1w/2+r2w/2) ){
		// r2 to the left, move r1 right
		if(xdirection > 0){
			xOverlap= (r1w/2+r2w/2) - abs(r1m1-r2m1);
		} else {
			xOverlap= -((r1w/2+r2w/2) - abs(r1m1-r2m1));
		}
	} else {
		xOverlap=0.0f;
	}

	// Get Y
	float r1y1 = r1.myTopLeft.y;
	float r1y2 = r1.myBottomRight.y;
	float r1h = r1y2-r1y1;
	float r1m2= r1h/2 + r1y1;

	float r2y1 = r2.myTopLeft.y;
	float r2y2 = r2.myBottomRight.y;
	float r2h = r2y2-r2y1;
	float r2m2= r2h/2 + r2y1;
	float ydirection = (r1m2-r2m2)>0?1:-1;
	float yOverlap;

	if (abs(r1m2-r2m2) < (r1h/2+r2h/2) ){
		// r2 to the left, move r1 right
		if(ydirection > 0){
			yOverlap=(r1h/2+r2h/2)- abs(r1m2-r2m2);
		} else {
			yOverlap=-((r1h/2+r2h/2) - abs(r1m2-r2m2));
		}
	} else {
		yOverlap = 0.0f;
	}

	if(abs(xOverlap) > 0.f && abs(yOverlap) > 0){
		if (abs(xOverlap) < abs(yOverlap)) {
			return float2(xOverlap,0.f);
		} else {
			return float2(0.f,yOverlap);
		}
	} else {
		return float2(0.f,0.f);
	}
}

void Hero::setSpawnPortal( bool aSpawn )
{
	mySpawnPortal = aSpawn;	
}