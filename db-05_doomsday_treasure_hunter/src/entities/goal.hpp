#ifndef DB_GOAL_HPP
#define DB_GOAL_HPP

#include "entity.hpp"
#include "animation.hpp"

#include <list>

class Goal : public Entity
{
public:
	Goal(int x, int y);

	virtual ~Goal();

	void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);

	 void logic(Level *Level);

	 void handleCollision(Entity *other, Level* level);
    
     bool drawInLayer(unsigned int layer) { return layer == Entity::AFTER_TILES_LAYER; }

protected:
    bool mTriggered;

	int mFrame;

	class Particle {
	public:
		Particle(float x_, float speed_) : x(x_), y(16), time(0), speed(speed_) { }
		float x, y, speed;
		int time;
	};

	std::list<Particle> mParticles;
	Animation mSprite;
};

#endif
