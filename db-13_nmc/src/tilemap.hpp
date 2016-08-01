#ifndef NMC_TILEMAP_HPP
#define NMC_TILEMAP_HPP

#include <allegro.h>

namespace nmc
{
    class TileMap
    {
    public:
        TileMap();
        ~TileMap();
        void save();
        void load(int roomNumber);
        void draw(BITMAP* dest, int scrollX, int scrollY, unsigned int layer);
		bool isSolid(int x, int y);
		bool isPlatform(int x, int y);
		int getTile(int x, int y);
        int getTileFlags(int x, int y);
        void setTile(int x, int y, int tileNumber);
        void setTileFlags(int x, int y, int flags);
        void setTileEntity(int x, int y, int entityNumber);
        int getTileEntity(int x, int y);
		int getWidth();
		int getHeight();
        void setShowSolidity(bool showSolidity);
        void setShowBackgroundLayer(bool showBackgroundLayer);
        void setShowForegroundLayer(bool showForegroundLayer);
        void setShowEntities(bool showEntities);

        static const int SOLID = 1;
        static const int PLATFORM = 2;
        static const int ICE = 4;
        static const int BACKGROUND = 8;

        static const int FOREGROUND_LAYER = 0;
        static const int BACKGROUND_LAYER = 1;
        static const int ENTITY_LAYER = 2;

    protected:
        void drawTile(BITMAP* dest, int x, int y, int tileNumber);
        void drawEntity(BITMAP* dest, int x, int y, int entityNumber);
        void drawFlags(BITMAP* dest, int x, int y, int flags);

        BITMAP* mTileMapBitmap;
        BITMAP* mEntityMapBitmap;
        BITMAP* mTileSetBitmap;
        BITMAP* mEntitySetBitmap;
        bool mShowSolidity;
        bool mShowForegroundLayer;
        bool mShowBackgroundLayer;
        bool mShowEntities;
        int mRoomNumber;
    };
}
#endif
