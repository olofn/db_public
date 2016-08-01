#ifndef NMC_ENTITY_HPP
#define NMC_ENTITY_HPP

#include <allegro.h>

namespace nmc
{
	class Room;
	class TileMap;

	class Entity
	{
	public:
		Entity(bool collidable = false, bool solid = false);
		
		Entity(int x, int y, int w = 0, int h = 0, bool collidable = false, bool solid = false);

		virtual ~Entity() { };

		virtual void setSize(int w, int h);

		virtual void setPosition(int x, int y);

		virtual int getX();

		virtual int getY();

		virtual int getWidth(); 

		virtual int getHeight();

		virtual void setX(int x);

		virtual void setY(int y);

		virtual void setWidth(int w); 

		virtual void setHeight(int h);

		virtual int getCenterX();

		virtual int getCenterY();

		virtual bool collidesWith(Entity *other, bool proximityDetection = false);

		virtual void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer) = 0;

		virtual void initialize(Room *room) { };

		virtual void logic(Room *room) = 0;

		virtual bool isToBeDeleted() = 0;

		virtual bool isSolid();

		virtual bool isCollidable();

		virtual void handleCollision(Entity *other, Room *room);

        virtual bool drawInLayer(unsigned int layer) { return layer == PLAYER_LAYER; }

        static const int BACKGROUND_LAYER = 0;
        static const int PLAYER_LAYER = 1;
        static const int FOREGROUND_LAYER = 2;

	protected:
		virtual bool solidAbove(Room* room, int& offset);

		virtual bool solidBelow(Room* room, int& offset);

		virtual bool platformBelow(Room *room, int& offset);

		virtual bool solidLeft(Room *room, int& offset);

		virtual bool solidRight(Room *room, int& offset);

		int mX, mY, mW, mH;
		bool mCollidable, mSolid;
	};
}
#endif