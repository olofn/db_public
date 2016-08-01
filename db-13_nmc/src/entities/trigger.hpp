#ifndef NMC_CUTSCENETRIGGER_HPP
#define NMC_CUTSCENETRIGGER_HPP

#include "entity.hpp"

namespace nmc
{
    class Trigger: public Entity
    {
    public:
        Trigger(Entity* entity, int x, int y, int width, int height, bool freezePlayer = false);
        
	    void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);

		void initialize(Room *room);

	    void logic(Room *room);

	    bool isToBeDeleted();

        bool drawInLayerdrawInLayer(unsigned int layer) { return false; }

        void handleCollision(Entity *other, Room *room);

    private:
        Entity* mEntity;
        bool mTriggered;
        bool mToBeDeleted;
        bool mFreezePlayer;
    };
}

#endif