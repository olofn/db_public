#include "Hero.hpp"
#include "Input.hpp"
#include "Constants.hpp"
#include "Room.hpp"
#include "Coin.hpp"
#include "Time.hpp"
#include "Animation.hpp"
#include "Sound.hpp"
#include "ParticleSystem.hpp"
#include "Resource.hpp"
#include "GameState.hpp"
#include "Camera.hpp"
#include "PlayerSkill.hpp"

static const float GROUND_ACCELERATION	= 6.5f;
static const float GROUND_DRAG			= 0.97f;
static const float GROUND_STOP_VELOCITY	= 4.5f;
static const float AIR_ACCELERATION		= 4.5f;
static const float AIR_DRAG				= 0.98f;
static const float JUMP_GRAVITY			= 3.0f;
static const float GRAVITY				= 6.0f;
static const float JUMP_VELOCITY		= 160.0f;
static const float ROPE_SPEED			= 700.0f;
static const float ROPE_REST_LENGTH		= 45.0f;
static const float ROPE_MAX_ACCELERATION= 12.0f;
static const float ROPE_SPRING_CONSTANT = 0.6f;
static const int   ROPE_DISSAPPEAR_TICKS= 6;
static const int   BLINKING_TICKS		= 100;
static const float KILL_VELOCITY		= 200.0f;
static const int   MIN_DEATH_COIN_LIFETIME	= 300;
static const int   MAX_DEATH_COIN_LIFETIME	= 500;

Hero::Hero()
	: mOnGround(false)
	, mJumpHeld(false)
	, mJumpPrepressed(false)
	, mFrame(0)
	, mRopeState(RopeState_Retracted)
	, mHookedEntity(0)
	, mFacingDirection(Direction_Right)
	, mBlinkingTicksLeft(0)
	, mRopeDissapearCounter(0)
	, mAnimationRun("data/images/hero_run.bmp", 4)
	, mAnimationJump("data/images/hero_jump.bmp", 1)
	, mAnimationFall("data/images/hero_fall.bmp", 1)
	, mAnimationRope("data/images/rope.bmp", 1)
	, mAnimationHook("data/images/hook.bmp", 1)
	, mAnimationHurt("data/images/hero_hurt.bmp", 1)
	, mSpawnPoint(-200,-200)
	, mRopeMaxLenghth(180)
	, myIsDead(false)
	, myImortal(false)
{
	mSize = float2(10.0f, 15.0f);
	mAnimationHookParticle = Resource::getAnimation("data/images/particles.bmp");
}

Hero::~Hero()
{
}

void Hero::update()
{
	if (myIsDead)
		return;

	Entity::update();

	if (mSpawnPoint.x < -100 && mSpawnPoint.y < -100)
	{
		mSpawnPoint = getPosition();
	}

	if (mRopeState == RopeState_Dissapearing) {
		mRopeDissapearCounter++;
		if (mRopeDissapearCounter >= ROPE_DISSAPPEAR_TICKS) {
			mRopeState = RopeState_Retracted;
		}
	}

	float acceleration = mOnGround ? GROUND_ACCELERATION : AIR_ACCELERATION;
	bool airRunning = false;

	if (Input::isHeld(Button_Left)) {
		mVelocity.x -= acceleration;

		if (mRopeState == RopeState_Attached && !mOnGround) {
			mFacingDirection = Direction_Left;
			airRunning = true;
			mMovementState = MovementState_AirRun;
		}
	}

	if (Input::isHeld(Button_Right)) {
		mVelocity.x += acceleration;

		if (mRopeState == RopeState_Attached && !mOnGround) {
			mFacingDirection = Direction_Right;
			airRunning = true;
			mMovementState = MovementState_AirRun;
		}
	}

	if (Input::isPressed(Button_Jump)) {
		if (!mJumpPrepressed && mOnGround)
			Sound::playSample("data/sounds/jump.wav");
		mJumpPrepressed = true;
	}

	if (mOnGround && mJumpPrepressed) {
		mVelocity.y = -JUMP_VELOCITY;
		if (mRopeState != RopeState_Attached) {
			mJumpHeld = true;
		}
		mJumpPrepressed = false;
	}

	if (Input::isReleased(Button_Jump)) {
		if (mJumpHeld && mVelocity.y < 0) {
			mVelocity.y *= 0.5f;
		}

		mJumpHeld = false;
		mJumpPrepressed = false;
	}

	if (Input::isReleased(Button_Fire)) {
		detachHook();
	}

	if (mVelocity.y >= 0) {
		mJumpHeld = false;
	}

	if (!airRunning) {
		mMovementState = MovementState_Still;
	}

	if (mOnGround) {
		if (mVelocity.x > 0) {
			mFacingDirection = Direction_Right;
		} else if (mVelocity.x < 0) {
			mFacingDirection = Direction_Left;
		}

		if (abs(mVelocity.x) > GROUND_STOP_VELOCITY)
		{
			mMovementState = MovementState_Run;
		}
	}
	else if (!airRunning)
	{
		if (mVelocity.y > 0)
			mMovementState = MovementState_Jump;
		else
			mMovementState = MovementState_Fall;
	}

	if (mMovementState == MovementState_Still)
	{
		mVelocity.x = 0;
	}

	if (Input::isPressed(Button_Fire)) {
		Sound::playSample("data/sounds/rope.wav");
		mRopeState = RopeState_Moving;
		mRopePosition = mPosition;
		mRopeVelocity = float2::ZERO;

		if (Input::isHeld(Button_Left)) {
			mRopeVelocity.x -= 1;
		}

		if (Input::isHeld(Button_Right)) {
			mRopeVelocity.x += 1;
		}

		if (Input::isHeld(Button_Up)) {
			mRopeVelocity.y -= 1;
		}

		if (Input::isHeld(Button_Down)) {
			mRopeVelocity.y += 1;
		}

		if (floatIsZero(mRopeVelocity)) {
			mRopeVelocity.x = (mFacingDirection == Direction_Left ? -1 : 1);
		}

		mRopeVelocity = adjustRopeDirection(normalize(mVelocity + normalize(mRopeVelocity) * ROPE_SPEED)) * ROPE_SPEED;

		if (mRopeVelocity.x < 0) {
			mFacingDirection = Direction_Left;
		} else if (mRopeVelocity.x > 0) {
			mFacingDirection = Direction_Right;
		}
	}

	if (mRopeState == RopeState_Moving) {
		const int substeps = 25;
		for (int i = 0; i < substeps; i++) {
			mRopePosition += mRopeVelocity / (substeps * Time::TicksPerSecond);
			int tileX = (int)(mRopePosition.x / mRoom->getTileWidth());
			int tileY = (int)(mRopePosition.y / mRoom->getTileHeight());
			if (mRoom->isHookable(tileX, tileY)) {
				//Sound::stopSample("data/sounds/rope.wav");
				Sound::playSample("data/sounds/hook.wav");
				mRopeState = RopeState_Attached;
				mJumpHeld = false;

				ParticleSystem* particleSystem = new ParticleSystem(
					mAnimationHookParticle,
					2,
					30,
					10,
					1,
					50,
					10,
					-normalize(mRopeVelocity)*10,
					1.0);

				particleSystem->setPosition(mRopePosition);

				mRoom->addEntity(particleSystem);

				break;
			}

			if (length(mRopePosition-mPosition) > mRopeMaxLenghth)
			{
				detachHook();
				Sound::playSample("data/sounds/no_hook.wav");
				break;
			}

			if (mRoom->isCollidable(tileX, tileY)) {
				detachHook();
				Sound::playSample("data/sounds/no_hook.wav");
				break;
			}

			if (mRoom->damageDone((int)(mRopePosition.x), (int)(mRopePosition.y))) {
				detachHook();
				break;
			}

			mHookedEntity = mRoom->findHookableEntity(mRopePosition);
			if (mHookedEntity != 0) {
				Sound::playSample("data/sounds/hook.wav");
				mRopeState = RopeState_Attached;
				mJumpHeld = false;
				mHookedEntityOffset = mRopePosition - mHookedEntity->getPosition();
				mHookedEntityOffset.x = floor(mHookedEntityOffset.x);
				mHookedEntityOffset.y = floor(mHookedEntityOffset.y);
			}
		}
	}

	if (mRopeState == RopeState_Attached) {
		if (mHookedEntity != 0) {
			mRopePosition = mHookedEntity->getPosition() + mHookedEntityOffset;
		}

		float2 ropeToHero = mPosition - mRopePosition;
		if (lengthCompare(ropeToHero, ROPE_REST_LENGTH) > 0) {
			float2 ropeRestPoint = mRopePosition + normalize(ropeToHero) * ROPE_REST_LENGTH;
			float2 heroToRestPoint = ropeRestPoint - mPosition;
			float2 ropeAcceleration = heroToRestPoint * ROPE_SPRING_CONSTANT;
			if (lengthCompare(ropeAcceleration, ROPE_MAX_ACCELERATION) > 0) {
				ropeAcceleration = normalize(ropeAcceleration) * ROPE_MAX_ACCELERATION;
			}
			mVelocity += ropeAcceleration;
		}

		if (Input::isHeld(Button_Up)) {
			mVelocity.y -= acceleration;
		}

		if (Input::isHeld(Button_Down)) {
			mVelocity.y += acceleration;
		}

		int ropeTileX = (int)(mRopePosition.x / mRoom->getTileWidth());
		int ropeTileY = (int)(mRopePosition.y / mRoom->getTileWidth());
		if (mHookedEntity == 0 && !mRoom->isHookable(ropeTileX, ropeTileY)) {
			detachHook();
		}
	}

	unsigned int bumps = moveWithCollision();
	
	if ((bumps & (Direction_Left | Direction_Right)) != 0) {
		mVelocity.x = 0;
	}

	if ((bumps & (Direction_Up | Direction_Down)) != 0) {
		mVelocity.y = 0;
	}

	float gravity = mJumpHeld ? JUMP_GRAVITY : GRAVITY;
	mVelocity.y += gravity;
	bool ground = ((bumps & Direction_Down) != 0);
	if (ground && !mOnGround && mRopeState != RopeState_Attached)
	{
		Sound::playSample("data/sounds/land.wav");
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
	int x = getDrawPositionX();
	int y = getDrawPositionY();

	if (myIsDead)
	{
		mAnimationHurt.drawFrame(buffer,
			0, 
			offsetX + x - mAnimationHurt.getFrameWidth()/2, 
			offsetY + y+getHalfSize().y-mAnimationHurt.getFrameHeight(),
			mFacingDirection == Direction_Left);
		return;
	}

	Animation* animation = 0;
	int frame = 1;

//	mMovementState = MovementState_Jump;

	switch(mMovementState)
	{
	case MovementState_Run:
		animation = &mAnimationRun;
		frame = mFrame/10;
		break;
	case MovementState_AirRun:
		animation = &mAnimationRun;
		frame = mFrame/3;
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

	if (mRopeState != RopeState_Retracted && (mRopeState != RopeState_Dissapearing || (mRopeDissapearCounter & 1) != 0)) {
		int x2 = getDrawPositionX() + offsetX;
		int y2 = getDrawPositionY() + offsetY;
		int x1 = (int)(mRopePosition.x + 0.5f) + offsetX;
		int y1 = (int)(mRopePosition.y + 0.5f) + offsetY;
		
		float2 line(x2-x1, y2-y1);
		int rlength = length(line);
		line /= length(line);
		line *= 3;
		
		float x = x1;
		float y = y1;
		
		int segments = (int)ceil(rlength/length(line));

		for (int i = 0; i < segments; i++)
		{
			float2 wave;

			if ((mRopeState == RopeState_Moving || mRopeState == RopeState_Dissapearing) && segments > 1) {
				float t = i / (float)(segments - 1);
				float value = sin(t * 3.141592) * sin(i * 0.3f);
				wave = float2(line.y, -line.x) * value;
			}

			mAnimationRope.drawFrame(buffer,
				frame, 
				x + wave.x - mAnimationRope.getFrameWidth()/2, 
				y + wave.y - mAnimationRope.getFrameHeight()/2);

			x += line.x;
			y += line.y;
		}

		mAnimationHook.drawFrame(buffer,
			frame, 
			x1 - mAnimationHook.getFrameWidth()/2, 
			y1 - mAnimationHook.getFrameHeight()/2);

	}

	if (mBlinkingTicksLeft > 0 && !mOnGround)
	{
		animation = &mAnimationHurt;
	}

	if ((mBlinkingTicksLeft/6)%2 == 0)
	{
		animation->drawFrame(buffer,
			frame, 
			offsetX + x - animation->getFrameWidth()/2, 
			offsetY + y+getHalfSize().y-animation->getFrameHeight(),
			mFacingDirection == Direction_Left);
	}
}

bool Hero::gotCoin()
{
	if (!mBlinkingTicksLeft)
	{
		GameState::put("coins", GameState::getInt("coins") + 1);
		return true;
	}

	return false;
}

void Hero::kill()
{
	if (myImortal)
		return;

	if (!mBlinkingTicksLeft)
	{
		PlayerSkill::playerDidSomethingStupid(0.0f, 0.1f);
		detachHook();

		int coins = GameState::getInt("coins");
		GameState::put("coins", 0);

		if (coins)
		{
			coins /= 2;
			coins = clamp(coins, 0,20);
			int lifetime = lerp(MAX_DEATH_COIN_LIFETIME, MIN_DEATH_COIN_LIFETIME, PlayerSkill::get());
			Coin::SpawnDeathCoins(coins, getPosition(), lifetime, mRoom);
			mBlinkingTicksLeft = BLINKING_TICKS;
			mVelocity = -(normalize(mVelocity)*KILL_VELOCITY);
			Sound::playSample("data/sounds/hurt.wav");
		}
		else
		{
			PlayerSkill::playerDidSomethingStupid(0.0f, 0.25f);
			die();
		}
	}
}

float2 Hero::adjustRopeDirection(float2 direction)
{
	float bestScore = 0;
	float2 bestDirection = direction;

	for (int y = 0; y < mRoom->getHeightInTiles(); y++) {
		for (int x = 0; x < mRoom->getWidthInTiles(); x++) {
			if (mRoom->isHookable(x, y)) {
				float pixelX = x * mRoom->getTileWidth() + mRoom->getTileWidth() / 2;
				float pixelY = y * mRoom->getTileHeight() + mRoom->getTileHeight() / 2;
				float2 tilePos(pixelX, pixelY);
				float score = getAutoAimScore(direction, tilePos);

				if (score > bestScore) {
					float2 direction = tilePos - mPosition;
					int rcX, rcY;
					bool rcHit = mRoom->rayCast(mPosition, direction, false, rcX, rcY);
					if (rcHit && rcX == x && rcY == y) {
						bestScore = score;
						bestDirection = direction;
					}
				}
			}
		}
	}

	std::vector<Entity *> &damagableEntities = mRoom->getDamagableEntities();
	std::vector<Entity *> &hookableEntities = mRoom->getHookableEntities();
	std::vector<Entity *> entities;
	entities.insert( entities.end(), damagableEntities.begin(), damagableEntities.end() );
	entities.insert( entities.end(), hookableEntities.begin(), hookableEntities.end() );

	for (int i = 0; i < (int)entities.size(); i++) {
		Entity *e = entities[i];
		float2 entityPos = e->getPosition();
		float score = getAutoAimScore(direction, entityPos);

		if (score > bestScore) {
			float2 direction = entityPos - mPosition;
			int rcX, rcY;
			bool rcHit = mRoom->rayCast(mPosition, direction, false, rcX, rcY);
			float2 rcTilePos(rcX * mRoom->getTileWidth() + mRoom->getTileWidth() / 2, rcY * mRoom->getTileHeight() + mRoom->getTileHeight() / 2);

			if (!rcHit || lengthCompare(direction, rcTilePos) < 0) {
				bestScore = score;
				bestDirection = direction;
			}
		}
	}

	return normalize(bestDirection);
}

float Hero::getAutoAimScore(float2 direction, float2 autoAimPos) {
	float2 playerToTile = autoAimPos - mPosition;
	float dotValue = dot(direction, playerToTile);
	if (dotValue < 0) {
		return -1;
	}
	float distance = length(playerToTile);
	dotValue /= distance;
	if (dotValue < 0.80) {
		return -1;
	}
	return pow(dotValue, 10.0f) / distance;
}

void Hero::die()
{
	mRopeState = RopeState_Retracted;
	mHookedEntity = 0;
	myIsDead = true;
	Sound::playSample("data/sounds/start.wav");
}

void
Hero::setLastSpawnPoint( float2 aPosition )
{
	mSpawnPoint = aPosition;
}

void Hero::detachHook()
{
	if (mRopeState != RopeState_Retracted && mRopeState != RopeState_Dissapearing) {
		mRopeState = RopeState_Dissapearing;
		mRopeDissapearCounter = 0;
	}
	mHookedEntity = 0;
}

Hero::RopeState Hero::getRopeState()
{
	return mRopeState;
}

float2 Hero::getRopePosition()
{	
	return mRopePosition;
}

bool Hero::hasHook()
{
	return mRopeState == RopeState_Attached;
}

Entity::CollisionRect Hero::getHookCollisionRect()
{
	CollisionRect rect;
	rect.myTopLeft = mRopePosition - float2(2,2);
	rect.myBottomRight = mRopePosition + float2(2,2);
	return rect;
}

bool Hero::gotCore()
{
	return true;
}

Direction Hero::getFacingDirection()
{
	return mFacingDirection;
}

Entity *Hero::getHookedEntity()
{	
	return mHookedEntity;
}

void Hero::respawn()
{
	setPosition(mSpawnPoint);
	setVelocity(float2(0,0));
	myIsDead = false;
	GameState::put("coins", 0);
	mOnGround = false;
	mJumpHeld= false;
	mJumpPrepressed = false;
	mFrame = 0;
	mRopeState = RopeState_Retracted;
	mHookedEntity = 0;
	mFacingDirection = Direction_Right;
	mBlinkingTicksLeft = 0;
	mRopeDissapearCounter = 0;
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