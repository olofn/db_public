#include "Spike.hpp"

#include "Room.hpp"
#include "Hero.hpp"

#include "Resource.hpp"

void Spike::update()
{
 	Hero* hero = mRoom->getHero();
	
	if (Collides(hero->getCollisionRect(), getCollisionRect()))
	{
		hero->kill();
	}
}

Spike::Spike()
: mSpikeTile(Resource::getBitmap("data/images/tileset1.bmp"), 70, 0, 10, 10)
{
	setSize(float2(10,10));
}

void Spike::draw( BITMAP *buffer, int offsetX, int offsetY, int layer )
{
	float2 pos = getPosition()-getHalfSize();
	mSpikeTile.onDraw(buffer, offsetX+pos.x, offsetY+pos.y);
}

Entity::CollisionRect Spike::getCollisionRect()
{
	CollisionRect rect = Entity::getCollisionRect();
	rect.myTopLeft.y += 5;
	return rect;
}