#include "tilemap.hpp"

#include "fileutil.hpp"
#include "music.hpp"
#include "exception.hpp"
#include "stringutil.hpp"

#include <iostream>

TileMap::TileMap(const std::string& filename)
{
    load(filename);
}
TileMap::~TileMap()
{

}

bool TileMap::isOnGround(Entity* entity)
{
    if (getTileAtPixel(entity->getX() + 2, 
                       entity->getY() + entity->getHeight())->isSolid())
        return true;
    if (getTileAtPixel(entity->getX() + entity->getWidth() - 3, 
                       entity->getY() + entity->getHeight())->isSolid())
        return true;
    
    return false;
}

bool TileMap::isInSolid(Entity* entity)
{
    if (getTileAtPixel(entity->getX() + 2, 
                       entity->getY() + 1)->isSolid())
        return true;
    if (getTileAtPixel(entity->getX() + entity->getWidth() - 3, 
                       entity->getY() + 1)->isSolid())
        return true;
    
    return false;
}

bool TileMap::isRightSolid(Entity* entity)
{
    if (getTileAtPixel(entity->getX() + entity->getWidth() - 1, 
                       entity->getY())->isSolid())
        return true;
    if (getTileAtPixel(entity->getX() + entity->getWidth() - 1, 
                       entity->getY() + entity->getHeight() - 1)->isSolid())
        return true;
    
    return false;
}

bool TileMap::isPeekLeftBelowSolid(Entity* entity)
{
    if (getTileAtPixel(entity->getX(), 
                       entity->getY() + 16)->isSolid())
        return true;
    if (getTileAtPixel(entity->getX(), 
                       entity->getY() + entity->getHeight() - 1  + 16)->isSolid())
        return true;
    
    return false;
}

bool TileMap::isPeekRightBelowSolid(Entity* entity)
{
    if (getTileAtPixel(entity->getX() + entity->getWidth() + 2, 
                       entity->getY() + 16)->isSolid())
        return true;
    if (getTileAtPixel(entity->getX() + entity->getWidth() + 2, 
                       entity->getY() + entity->getHeight() - 1 + 16)->isSolid())
        return true;
    
    return false;
}

bool TileMap::isPeekRightSolid(Entity* entity)
{
    if (getTileAtPixel(entity->getX() + entity->getWidth() + 2, 
                       entity->getY())->isSolid())
        return true;
    if (getTileAtPixel(entity->getX() + entity->getWidth() + 2, 
                       entity->getY() + entity->getHeight() - 1)->isSolid())
        return true;
    
    return false;
}

bool TileMap::isLeftSolid(Entity* entity)
{
    if (getTileAtPixel(entity->getX(), 
                       entity->getY())->isSolid())
        return true;
    if (getTileAtPixel(entity->getX(), 
                       entity->getY() + entity->getHeight() - 1)->isSolid())
        return true;
    
    return false;
}

bool TileMap::isPeekLeftSolid(Entity* entity)
{
    if (getTileAtPixel(entity->getX() - 3, 
                       entity->getY())->isSolid())
        return true;
    if (getTileAtPixel(entity->getX() - 3, 
                       entity->getY() + entity->getHeight() - 1)->isSolid())
        return true;
    
    return false;
}

bool TileMap::isAboveSolid(Entity* entity)
{
    if (getTileAtPixel(entity->getX(), 
                       entity->getY() - 1)->isSolid())
        return true;
    if (getTileAtPixel(entity->getX() + entity->getWidth() - 1, 
                       entity->getY() - 1)->isSolid())
        return true;
    
    return false;
}

bool TileMap::isPeekAboveSolid(Entity* entity)
{
    if (getTileAtPixel(entity->getX(), 
                       entity->getY() - 16)->isSolid())
        return true;
    if (getTileAtPixel(entity->getX() + entity->getWidth() - 1, 
                       entity->getY() - 16)->isSolid())
        return true;
    
    return false;
}

void TileMap::alignToGroundTile(Entity* entity)
{
    entity->setPosition(entity->getX(), 
                        entity->getY() - (entity->getY() % 16));
}

void TileMap::alignToAboveTile(Entity* entity)
{
    entity->setPosition(entity->getX(), 
                        entity->getY() - (entity->getY() % 16) + 16);
}


void TileMap::alignToRightTile(Entity* entity)
{
    entity->setPosition(entity->getX() - (entity->getX() % 16), 
                        entity->getY());
}

void TileMap::alignToLeftTile(Entity* entity)
{
    entity->setPosition(entity->getX() - (entity->getX() % 16) + 16, 
                        entity->getY());
}

Tile* TileMap::getTileAtPixel(int x, int y)
{
    return getTile(x / 16, y / 16);
}

void TileMap::replaceTile(Tile* tile)
{
    int x = tile->getX() / 16;
    int y = tile->getY() / 16;

    if (x < 0)
	{
        throw DB_EXCEPTION("Cannot replace a tile that is out of bounds");
	}

	if (y < 0)
	{
		throw DB_EXCEPTION("Cannot replace a tile that is out of bounds");
	}

	if (x >= mWidth)
	{
		throw DB_EXCEPTION("Cannot replace a tile that is out of bounds");
	}

	if (y >= mHeight)
	{
		throw DB_EXCEPTION("Cannot replace a tile that is out of bounds");
	}

    if ( mTiles[x + y * mWidth] != NULL)
        delete  mTiles[x + y * mWidth];
    mTiles[x + y * mWidth] = tile;
}

void TileMap::draw(BITMAP* dest, int scrollX, int scrollY)
{
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
  
    int tileMapEndX = scrollX / 16 + dest->w / 16 + 2;

    if (tileMapEndX > getWidth())
    {
        tileMapEndX = getWidth();
    }

    int tileMapEndY = scrollY / 16 + dest->h / 16 + 2;

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
            getTile(x, y)->draw(dest, scrollX, scrollY);
        }
    }
}

Tile* TileMap::getTile(int x, int y)
{
    if (x < 0)
	{
		x = 0;
	}

	if (y < 0)
	{
		y = 0;
	}

	if (x >= mWidth)
	{
		x = mWidth - 1;
	}

	if (y >= mHeight)
	{
		y = mHeight - 1;
	}

    return mTiles[x + y * mWidth];
}

void TileMap::load(const std::string& filename)
{
    std::cout << "Loading tilemap " + filename + "...";
    std::vector<std::string> data = tokenize(loadFile(filename), "\n");

    data.erase(data.begin()); // Discard level name
    data.erase(data.begin()); // Discard stars to unlock
    data.erase(data.begin()); // Discard level time
    data.erase(data.begin()); // Discard level music

    unsigned int row;
    unsigned int col;
    
    mHeight = 0;

    // Load entities
    for (row = 0; row < data.size(); row++)
    {
		pollMusic();

        if (row == 0)
            mWidth = data[row].size();

        if (data[row] == "DIALOG")
        {
            break;
        }

        if ((int)data[row].size() < mWidth)
        {
            throw DB_EXCEPTION("Row number " + toString(row) + " is to short in file " + filename + ".");
        }
        else if ((int)data[row].size() > mWidth)
        {
            throw DB_EXCEPTION("Row number " + toString(row) + " is to long in file " + filename + ".");
        }

        mHeight++;

        for (col = 0; col < data[row].size(); col++)
        {
            //Entity* staticEntity = NULL;
			Entity* entity = NULL;

            switch(data[row].at(col))
            {
                case '.':
                    {
					Tile* tile = new Tile(col*16,row*16, "", false);
                    mTiles.push_back(tile);
                    }
                    break;
                case '1':
                    {
                    Tile* tile = new Tile(col*16,row*16, "block.bmp");
                    mTiles.push_back(tile);
                    }
                   break;
                default:
                    {
					Tile* tile = new Tile(col*16,row*16, "", false);
                    mTiles.push_back(tile);
                    }
            }
        }
    }

    std::cout << " Done!" << std::endl;
}
