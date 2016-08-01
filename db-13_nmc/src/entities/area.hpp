#ifndef NMC_AREA_HPP
#define NMC_AREA_HPP

#include "entity.hpp"
#include <string>

namespace nmc
{
    class Area: public Entity
    {
    public:
        Area(const std::string& name);
        
        void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);

	    void logic(Room *room);

	    bool isToBeDeleted();

        bool drawInLayerdrawInLayer(unsigned int layer) { return false; }
    protected:
        std::string mName;
        int mFrameCounter;
    };
}
#endif