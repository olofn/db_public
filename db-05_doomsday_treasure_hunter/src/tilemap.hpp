#ifndef DB_TILEMAP_HPP
#define DB_TILEMAP_HPP

#include "tile.hpp"

class TileMap
{
public:
    TileMap(const std::string& filename);
    ~TileMap();
    Tile* getTileAtPixel(int x, int y);
    void replaceTile(Tile* tile);
    void draw(BITMAP* dest, int scrolly, int scrollx);
    int getWidth() { return mWidth; }
    int getHeight() { return mHeight; }
    bool isInSolid(Entity* entity);
    bool isOnGround(Entity* entity);
    bool isRightSolid(Entity* entity);
    bool isPeekRightSolid(Entity* entity);
    bool isLeftSolid(Entity* entity);
    bool isPeekLeftSolid(Entity* entity);
    bool isAboveSolid(Entity* entity);
    bool isPeekAboveSolid(Entity* entity);
    bool isPeekLeftBelowSolid(Entity* entity);
    bool isPeekRightBelowSolid(Entity* entity);
    void alignToGroundTile(Entity* entity);
    void alignToRightTile(Entity* entity);
    void alignToLeftTile(Entity* entity);
    void alignToAboveTile(Entity* entity);
    

protected:
    Tile* getTile(int x, int y);
    void load(const std::string& filename);
    int mWidth;
    int mHeight;
    std::vector<Tile*> mTiles;
};

#endif
