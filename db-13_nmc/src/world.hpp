#ifndef NMC_WORLD_HPP
#define NMC_WOLRD_HPP

#include <map>
#include <vector>

namespace nmc
{
    class RoomPosition
    {
    public:
        RoomPosition()
            :x(0),
            y(0)
        {}
        RoomPosition(int x_, int y_)
            : x(x_),
              y(y_)
        {}
        int x;
        int y;
    };

    class World
    {
    public:
        static World* getInstance();

        void setRoomPosition(int roomNumber, RoomPosition roomPosition);
        RoomPosition getRoomPosition(int roomNumber);
        int getRoomAt(int x, int y);
        void save();
        std::vector<int> getRoomNumberList();

    private:
        World();
        void load();
        static World* mInstance;
        std::map<int, RoomPosition> mRoomPositions;
    };
}
#endif