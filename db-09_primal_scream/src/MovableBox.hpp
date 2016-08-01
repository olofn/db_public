#pragma once
#include "Entity.hpp"
#include "Animation.hpp"


class MovableBox : public Entity{
private:
	int mGravityHitTimer;
	Animation mBoxAnimation;
public:
	MovableBox();
	~MovableBox();
	void update();
	void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
	virtual bool isShootable() { return true; }
	int getLayer();
	void toggleGravityDirection(int timer);
	bool isSolid();
	void setInitialPosition(float2 position);
};