#include "Precompiled.hpp"

#include "MovableBox.hpp"

#include "Room.hpp"

MovableBox::MovableBox()
	:mBoxAnimation("data/images/movableblock.bmp",1)
	,mGravityHitTimer(0)
{
	setSize(float2(20.f,20.f));
}
MovableBox::~MovableBox(){
}

void MovableBox::update(){
	if (mGravityHitTimer <= 0){
		mGravityDirection=1;
	} else {
		mGravityHitTimer--;
	}
	// walk
	int cur_x = getPosition().x;
	int cur_y = getPosition().y;

	setVelocity(float2(0.0f,40.f*getGravityDirection()));
	
	//setVelocity(float2(12.0f,.0f));
	moveWithCollision();

	//mFrame ++;
}
bool MovableBox::isSolid() { 
	return true; 
}

void MovableBox::draw(BITMAP *buffer, int offsetX, int offsetY, int layer){
	int x = getDrawPositionX();
	int y = getDrawPositionY();

	int frame = 1;
	//frame = mFrame/4;
	
	bool gravityFlip = (getGravityDirection()>0)?false:true;

	mBoxAnimation.drawFrame(buffer,
		frame, 
		offsetX + x - mBoxAnimation.getFrameWidth()/2, 
		offsetY + y+getHalfSize().y-mBoxAnimation.getFrameHeight(),
		true,gravityFlip);
	
}
int MovableBox::getLayer(){return 1;}
void MovableBox::toggleGravityDirection(int timer){
	mGravityDirection*=-1;
	mGravityHitTimer=timer;
}
void MovableBox::setInitialPosition(float2 position){
	setPosition(float2(position.x+5,position.y));
}
