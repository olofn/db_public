#ifndef DB_MOVINGSPIKES_HPP
#define DB_MOVINGSPIKES_HPP

#include "entity.hpp"
#include "animation.hpp"

class MovingSpikes: public Entity
{
public:
    MovingSpikes(int x, int y, unsigned int orientation);

	void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);

	 void logic(Level *Level);

	 void handleCollision(Entity *other, Level* level);
    
     bool drawInLayer(unsigned int layer) { return layer == Entity::PLAYER_LAYER; }

    enum Orientation
    {
        CEILING,
        FLOOR
    };

protected:
    enum State
    {
        DOWN,
        UP,
        MOVING_DOWN,
        MOVING_UP
    };
    unsigned int mOrientation;
    Animation mAnimation;
    Animation mLightAnimation;
    int mFrameCounter;
    bool mHostile;
    State mState;
    int mFrame;
};

#endif
