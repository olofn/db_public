#ifndef DB_BUTTON_HPP
#define DB_BUTTON_HPP

#include "entity.hpp"
#include "animation.hpp"

class Button : public Entity
{
public:
	Button(int x, int y);

	virtual ~Button();

	void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);

	 void logic(Level *Level);

	 void handleCollision(Entity *other, Level* level);
    
     bool drawInLayer(unsigned int layer) { return layer == Entity::AFTER_TILES_LAYER; }

protected:
    bool mTriggered;

	Animation mAnimation;
    Animation mLightRayAnimation;
    bool mCollisionThisFrame;
};

#endif
