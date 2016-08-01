#pragma once

class Hero;

class Camera
{
public:
	Camera();
	float2	getOffset();
	void	onLogic(
				Hero* aHero,
				float2 aTopLeft,
				float2 aBottomRight);
	void	addShake(float amount, int aShakeTime);
	void	centerToHero(Hero* aHero);
	void	onRespawn();

private:
	float2 mOffset;
	float2 mShakeOffset;
	float myShakeAmount;
	int myShakeTime;
};