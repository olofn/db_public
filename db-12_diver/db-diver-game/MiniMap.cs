using System;
using System.Collections.Generic;
using System.Text;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using DB.Gui;

namespace DB.DoF
{    
    public class MiniMap
    {
        public const int DirectionUp = 1;
        public const int DirectionRight = 2;
        public const int DirectionLeft = 4;
        public const int DirectionDown = 8;

        Texture2D mapPaper;
        SpriteGrid mapTiles;
        int[,] rooms;
        int treasureX = 0;
        int treasureY = 5;
        

        public MiniMap(Sea sea)
        {
            mapPaper = DiverGame.DefaultContent.Load<Texture2D>("mappaper");
            mapTiles = new SpriteGrid("maptiles", 4, 5);
            rooms = new int[sea.Width, sea.Height];
            ClearDiscoveries();           
        }

        public void ClearDiscoveries()
        {
            for (int y = 0; y < rooms.GetLength(1); y++)
            {
                for (int x = 0; x < rooms.GetLength(0); x++)
                {
                    rooms[x, y] = -1;
                }
            }
        }

        public void Discover(Room room)
        {
            int direction = 0;
            int roomX = room.SeaX;
            int roomY = room.SeaY;

            for (int y = 1; y < room.TileMap.Height - 1; y++)
            {
                if (!room.TileMap.IsSolid(0, y)) direction |= DirectionLeft;
                if (!room.TileMap.IsSolid(room.TileMap.Width - 1, y)) direction |= DirectionRight;
            }

            for (int x = 1; x < room.TileMap.Width - 1; x++)
            {
                if (!room.TileMap.IsSolid(x, 0)) direction |= DirectionUp;
                if (!room.TileMap.IsSolid(x, room.TileMap.Height - 1)) direction |= DirectionDown;
            }

            rooms[roomX, roomY] = direction;
        }

        public void Draw(Graphics g, int currentRoomX, int currentRoomY)
        {
            Point contentSize = new Point(rooms.GetLength(0) * mapTiles.FrameSize.X, rooms.GetLength(1) * mapTiles.FrameSize.Y);
            g.PushClipRectangle(new Rectangle(200 - mapPaper.Width / 2, 150 - mapPaper.Height / 2 - 16, mapPaper.Width + 2, mapPaper.Height + 2));
            g.Begin();
            g.Draw(mapPaper, new Point(2, 2), new Color(0, 0, 0, 50));
            g.Draw(mapPaper, Point.Zero, new Color(255, 255, 255, 220));
            

            g.PushClipRectangle(new Rectangle((mapPaper.Width - contentSize.X) / 2, (mapPaper.Height - contentSize.Y) / 2, contentSize.X, contentSize.Y));

            for (int y = 0; y < rooms.GetLength(1); y++)
            {
                for (int x = 0; x < rooms.GetLength(0); x++)
                {
                    if (rooms[x, y] >= 0)
                    {
                        mapTiles.Draw(g, new Point(x * mapTiles.FrameSize.X, y * mapTiles.FrameSize.Y), rooms[x, y], new Color(255, 255, 255, 128));
                    }                
                }
            }

            mapTiles.Draw(g, new Point(currentRoomX * mapTiles.FrameSize.X, currentRoomY * mapTiles.FrameSize.Y), 17);
            mapTiles.Draw(g, new Point(treasureX * mapTiles.FrameSize.X, treasureY * mapTiles.FrameSize.Y), 19);

            g.PopClipRectangle();

            g.End();
            g.PopClipRectangle();
        }

    }
}
