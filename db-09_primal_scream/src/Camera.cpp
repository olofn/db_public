#include "Precompiled.hpp"

#include "Camera.hpp"

#include "Hero.hpp"
#include "Util.hpp"

float2 Camera::getOffset()
{
	return float2((int)(mOffset.x + mShakeOffset.x+0.5), (int)(mOffset.y + mShakeOffset.y+0.5));
}

void Camera::onLogic(Hero* aHero,
					 float2 aTopLeft,
					 float2 aBottomRight)
{
	float2 heroRealPos = aHero->getPosition();
	float2 desiredOffset;

	float2 heropos(-aHero->getDrawPositionX() + 320/2, -aHero->getDrawPositionY() + (2*240)/3);
	desiredOffset = heropos;

	mOffset += (desiredOffset-mOffset)*0.1;


	myShakeTime--;

	if (myShakeTime > 0)
	{
		mShakeOffset.x = myShakeAmount*(frand()-0.5f);
		mShakeOffset.y = myShakeAmount*(frand()-0.5f);
	}

	if (myShakeTime < 0)
	{
		mShakeOffset = float2();
	}

	mOffset.x = -clamp(-mOffset.x, aTopLeft.x, aBottomRight.x - 319);
	mOffset.y = -clamp(-mOffset.y, aTopLeft.y, aBottomRight.y - 239);

	/*if (mOffset.x+aTopLeft.x > 0)
	{
		mOffset.x = -aTopLeft.x;
	}

	if (mOffset.y+aTopLeft.y > 10)
	{
		mOffset.y = 10-aTopLeft.y;
	}

	if (mOffset.x+aBottomRight.x < 320)
	{
		mOffset.x = 320-aBottomRight.x;
	}

	if (mOffset.y+aBottomRight.y < 240)
	{
		mOffset.y = 240-aBottomRight.y;
	}
	*/
}

void Camera::addShake( float amount, int aShakeTime)
{
	myShakeAmount = amount;
	myShakeTime = aShakeTime;
}

Camera::Camera()
: myShakeAmount(0)
{

}

void Camera::centerToHero(Hero* aHero)
{
	float2 heropos(-aHero->getDrawPositionX() + 320/2, -aHero->getDrawPositionY() + (2*240)/3);
	mOffset = heropos;
}

void Camera::onRespawn()
{
	myShakeTime = 0;
	myShakeAmount = 0.0f;
}
