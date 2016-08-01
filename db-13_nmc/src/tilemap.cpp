#include "tilemap.hpp"

#include "resourcehandler.hpp"

#include <iostream>
namespace nmc
{
    TileMap::TileMap()
        : mShowSolidity(false),
        mShowBackgroundLayer(true),
        mShowForegroundLayer(true),
        mShowEntities(false),
        mTileMapBitmap(NULL),
        mRoomNumber(0)
    {
    }

    TileMap::~TileMap()
    {
        if (mTileMapBitmap != NULL)
        {
            destroy_bitmap(mTileMapBitmap);
        }
    }

    void TileMap::setShowSolidity(bool showSolidity)
    {
        mShowSolidity = showSolidity;
    }

    void TileMap::setShowBackgroundLayer(bool showBackgroundLayer)
    {
        mShowBackgroundLayer = showBackgroundLayer;
    }

    void TileMap::setShowForegroundLayer(bool showForegroundLayer)
    {
        mShowForegroundLayer = showForegroundLayer;
    }

    void TileMap::setShowEntities(bool showEntities)
    {
        mShowEntities = showEntities;
    }

    void TileMap::save()
    {
        BITMAP* tileMapBitmap = ResourceHandler::getInstance()->getRoomTilesBitmap(mRoomNumber);
        blit(mTileMapBitmap, tileMapBitmap, 0, 0, 0, 0, tileMapBitmap->w, tileMapBitmap->h);
        ResourceHandler::getInstance()->saveRoomBitmap(mRoomNumber);
    }

    void TileMap::load(int roomNumber)
    {
        mRoomNumber = roomNumber;

        if (mTileMapBitmap != NULL)
        {
            destroy_bitmap(mTileMapBitmap);
        }

        BITMAP* tileMapBitmap = ResourceHandler::getInstance()->getRoomTilesBitmap(roomNumber);
        mTileMapBitmap =  create_bitmap_ex(24, tileMapBitmap->w, tileMapBitmap->h);
        blit(tileMapBitmap, mTileMapBitmap, 0, 0, 0, 0, tileMapBitmap->w, tileMapBitmap->h);

        mEntityMapBitmap = ResourceHandler::getInstance()->getRoomEntitiesBitmap(roomNumber);

        mTileSetBitmap = ResourceHandler::getInstance()->getBitmap("tileset.bmp");
        mEntitySetBitmap = ResourceHandler::getInstance()->getBitmap("entityset.bmp");
    }

    void TileMap::draw(BITMAP* dest, int scrollX, int scrollY, unsigned int layer)
    {   
        if (!mShowForegroundLayer && layer == FOREGROUND_LAYER)
        {   
            return;
        }

        if (!mShowBackgroundLayer && layer == BACKGROUND_LAYER)
        {
            return;
        }

         if (!mShowEntities && layer == ENTITY_LAYER)
        {
            return;
        }

        int tileMapX = scrollX / 16;

        if (tileMapX < 0)
        {
            tileMapX = 0;
        }
      
        int tileMapY = scrollY / 16;
        
        // We ignore the first line as it's not a part of the tilemap.
        if (tileMapY < 0)
        {
            tileMapY = 0;
        }
      
        int tileMapEndX = scrollX / 16 + dest->w / 16 + 1;

        if (tileMapEndX > getWidth())
        {
            tileMapEndX = getWidth();
        }

        int tileMapEndY = scrollY / 16 + dest->h / 16 + 1;

        if (tileMapEndY > getHeight())
        {
            tileMapEndY = getHeight();
        }

        int y;
        for (y = tileMapY; y < tileMapEndY; y++)
        {
            int x;
            for (x = tileMapX; x< tileMapEndX; x++)
            {
                if (layer == ENTITY_LAYER)
                {
                    int g = getTileEntity(x, y);

                    if (g != 0)
                    {
                        drawEntity(dest, 
                                   x * 16 - scrollX, 
                                   y * 16 - scrollY, 
                                   g);
                    }
                }
                else
                {
                    int r = getTile(x, y);

                    int b = getTileFlags(x, y);

                    bool drawInLayer = (layer == FOREGROUND_LAYER && !(b & BACKGROUND)
                                      || (layer == BACKGROUND_LAYER && (b & BACKGROUND)));

                    if (r != 0 && drawInLayer)
                    {
                        drawTile(dest, 
                                 x * 16 - scrollX, 
                                 y * 16 - scrollY, 
                                 r);
                    }

                    if (mShowSolidity)
                    {
                        drawFlags(dest, 
                                  x * 16 - scrollX, 
                                  y * 16 - scrollY,
								  b);
                    }
				}
            }
        }
    }

    void TileMap::drawTile(BITMAP* dest, int x, int y, int tileNumber)
    {
        int tileSetX = (tileNumber % (mTileSetBitmap->w / 16)) * 16;
        int tileSetY = (tileNumber / (mTileSetBitmap->w / 16)) * 16;

        masked_blit(mTileSetBitmap,
                    dest,
                    tileSetX,
                    tileSetY,
                    x,
                    y,
                    16,
                    16);
    }

    void TileMap::drawEntity(BITMAP* dest, int x, int y, int entityNumber)
    {
        int entitySetX = (entityNumber % (mEntitySetBitmap->w / 16)) * 16;
        int entitySetY = (entityNumber / (mEntitySetBitmap->w / 16)) * 16;

        masked_blit(mEntitySetBitmap,
                    dest,
                    entitySetX,
                    entitySetY,
                    x,
                    y,
                    16,
                    16);
    }

    void TileMap::drawFlags(BITMAP* dest, int x, int y, int flags)
    {
		if (flags & SOLID)
		{
			rect(dest, x, y, x + 15, y + 15, makecol(0, 0, 0));
			rect(dest, x + 1, y + 1, x + 14, y + 14, makecol(255, 255, 255));
			rect(dest, x + 2, y + 2, x + 13, y + 13, makecol(0, 0, 0));
		}

		if (flags & PLATFORM)
		{
			rect(dest, x, y, x + 15, y + 3, makecol(0, 0, 0));
			hline(dest, x + 1, y + 1, x + 14, makecol(255, 255, 255));
		}

		if (flags & ICE)
		{
			rect(dest, x + 7, y + 3, x + 9, y + 12, makecol(0, 0, 0));
			vline(dest, x + 8, y + 4, y + 11, makecol(0, 255, 255));
		}
    }

	bool TileMap::isSolid(int x, int y) 
    {
		return getTileFlags(x, y) & SOLID;
	}

	bool TileMap::isPlatform(int x, int y) 
    {
		if (x < 0 || y < 0 || x >= getWidth() || y >= getHeight()) {
			return false;
		}

		return getTileFlags(x, y) & PLATFORM;
	}

    int TileMap::getWidth()
	{
		return mTileMapBitmap->w;
	}
	
	int TileMap::getHeight()
	{
		return mTileMapBitmap->h;
	}

	int TileMap::getTile(int x, int y) 
    {
		if (x < 0)
		{
			x = 0;
		}

		if (y < 0)
		{
			y = 0;
		}

		if (x >= getWidth())
		{
			x = getWidth() - 1;
		}

		if (y >= getHeight())
		{
			y = getHeight() - 1;
		}

        int pixel = _getpixel24(mTileMapBitmap, x, y);

		return getr24(pixel) | (getg24(pixel) << 8);
	}

    int TileMap::getTileFlags(int x, int y) 
    {
		if (x < 0)
		{
			x = 0;
		}

		if (y < 0)
		{
			y = 0;
		}

		if (x >= getWidth())
		{
			x = getWidth() - 1;
		}

		if (y >= getHeight())
		{
			y = getHeight() - 1;
		}

        return getb24(_getpixel24(mTileMapBitmap, x, y));
	}

    int TileMap::getTileEntity(int x, int y) 
    {
		if (x < 0)
		{
			x = 0;
		}

		if (y < 0)
		{
			y = 0;
		}

		if (x >= getWidth())
		{
			x = getWidth() - 1;
		}

		if (y >= getHeight())
		{
			y = getHeight() - 1;
		}

		return _getpixel24(mEntityMapBitmap, x, y);
	}

    void TileMap::setTile(int x, int y, int tileNumber)
    {
		if (x < 0 || y < 0 || x >= getWidth() || y >= getHeight())
		{
			return;
		}

        int pixel = _getpixel24(mTileMapBitmap, x, y);
        int newPixel = makecol24(tileNumber, 
                                 getg24(pixel), 
                                 getb24(pixel));
        _putpixel24(mTileMapBitmap, x, y, newPixel); 
    }

    void TileMap::setTileFlags(int x, int y, int flags)
    {
		if (x < 0 || y < 0 || x >= getWidth() || y >= getHeight())
		{
			return;
		}

        int pixel = _getpixel24(mTileMapBitmap, x, y);
        int newPixel = makecol24(getr24(pixel), 
                                 getg24(pixel), 
                                 flags);
        _putpixel24(mTileMapBitmap, x, y, newPixel); 
    }

     void TileMap::setTileEntity(int x, int y, int entityNumber)
    {
		if (x < 0 || y < 0 || x >= getWidth() || y >= getHeight())
		{
			return;
		}

        _putpixel24(mEntityMapBitmap, x, y, entityNumber); 
    }
}