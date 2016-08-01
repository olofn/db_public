#ifndef NMC_TEXT_HPP
#define NMC_TEXT_HPP

#include "entity.hpp"
#include <string>

namespace nmc
{
    class Text: public Entity
    {
    public:
        Text(const std::string& text, int timeToShowText = 150);

        virtual void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);

        virtual void logic(Room *room);

        virtual bool isToBeDeleted();

        virtual bool drawInLayer(unsigned int layer) { return false; }

    protected:
        std::string mText;
        int mFrameCounter;
        int mTimeToShowText;
    };
}

#endif