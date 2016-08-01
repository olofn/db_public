#include "entities/outsidecastlebackground.hpp"
#include "resourcehandler.hpp"
#include "room.hpp"

namespace nmc
{
    OutsideCastleBackground::OutsideCastleBackground()
        :mRoomWidth(240),
        mRoomHeight(240),
        mWind(0)
    {
        mCloudsBitmap1 = ResourceHandler::getInstance()->getBitmap("outside-castle-clouds1.bmp");
        mCloudsBitmap2 = ResourceHandler::getInstance()->getBitmap("outside-castle-clouds2.bmp");
        mCloudsBitmap3 = ResourceHandler::getInstance()->getBitmap("outside-castle-clouds3.bmp");

        mCastleBackgroundBitmap1 = ResourceHandler::getInstance()->getBitmap("outside-castle-background1.bmp");
        mCastleBackgroundBitmap2 = ResourceHandler::getInstance()->getBitmap("outside-castle-background2.bmp");
        mCastleBackgroundBitmap3 = ResourceHandler::getInstance()->getBitmap("outside-castle-background3.bmp");
        mCastleBackgroundBitmap4 = ResourceHandler::getInstance()->getBitmap("outside-castle-background4.bmp");
    }

    void OutsideCastleBackground::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
    {
         masked_blit(mCloudsBitmap3, 
                   dest,
                    ((mWind / 6)% 320), 
                    0,
                    0,
                    0,
                    mCloudsBitmap3->w,
                    mCloudsBitmap3->h);
        masked_blit(mCloudsBitmap3, 
                    dest,
                   ((mWind / 6)% 320) - 320, 
                    0,
                    0,
                    0,
                    mCloudsBitmap3->w,
                    mCloudsBitmap3->h);
        masked_blit(mCloudsBitmap2, 
                   dest,
                   ((mWind / 4) % 320),
                    0,
                    0,
                    0,
                    mCloudsBitmap2->w,
                    mCloudsBitmap2->h);
        masked_blit(mCloudsBitmap2, 
                    dest,
                   ((mWind / 4) % 320) - 320, 
                    0,
                    0,
                    0,
                    mCloudsBitmap2->w,
                    mCloudsBitmap2->h);
        masked_blit(mCloudsBitmap1, 
                   dest,
                   ((mWind / 2) % 320), 
                    0,
                    0,
                    0,
                    mCloudsBitmap1->w,
                    mCloudsBitmap1->h);
        masked_blit(mCloudsBitmap1, 
                    dest,
                   ((mWind / 2) % 320) - 320,
                    0,
                    0,
                    0,
                    mCloudsBitmap1->w,
                    mCloudsBitmap1->h);

        masked_blit(mCastleBackgroundBitmap4, 
                    dest,
                    0, 
                    0,
                    (mRoomWidth - scrollx - 320) / 10 + 320 - mCastleBackgroundBitmap4->w, 
                    - scrolly + mRoomHeight - mCastleBackgroundBitmap4->h,
                    mCastleBackgroundBitmap4->w,
                    mCastleBackgroundBitmap4->h);

        masked_blit(mCastleBackgroundBitmap3, 
                    dest,
                    0, 
                    0,
                    (mRoomWidth - scrollx - 320) / 8 + 320 - mCastleBackgroundBitmap3->w, 
                    - scrolly + mRoomHeight - mCastleBackgroundBitmap3->h - 10,
                    mCastleBackgroundBitmap3->w,
                    mCastleBackgroundBitmap3->h);

        masked_blit(mCastleBackgroundBitmap2, 
                    dest,
                    0, 
                    0,
                    (mRoomWidth - scrollx - 320) / 6 + 320 - mCastleBackgroundBitmap2->w, 
                    - scrolly + mRoomHeight - mCastleBackgroundBitmap2->h - 10,
                    mCastleBackgroundBitmap2->w,
                    mCastleBackgroundBitmap2->h);

        masked_blit(mCastleBackgroundBitmap1, 
                    dest,
                    0, 
                    0,
                    (mRoomWidth - scrollx - 320) / 4 + 320 - mCastleBackgroundBitmap1->w, 
                     - scrolly + mRoomHeight - mCastleBackgroundBitmap1->h - 10,
                    mCastleBackgroundBitmap1->w,
                    mCastleBackgroundBitmap1->h);
    }

    void OutsideCastleBackground::logic(Room* room)
    {
        mRoomWidth = room->getTileMap()->getWidth() * 16;    
        mRoomHeight = room->getTileMap()->getHeight() * 16;

        mWind++;
    }
}