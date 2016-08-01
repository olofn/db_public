using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using DB.DoF.Entities;
using DB.Gui;

namespace DB.DoF.Tools
{
    public class BombTool : ITool
    {
        Texture2D icon;
        public Texture2D Icon { get { return icon; } }
        int coolDown = 0;

        public BombTool()
        {
            icon = DiverGame.DefaultContent.Load<Texture2D>("iconbomb");
        }

        public void Update(Diver diver, Room room, State s)
        {
            if(coolDown > 0) coolDown--;

        }

        public void OnUse(Diver diver, Room room)
        {
            if (coolDown <= 0)
            {
                room.AddEntity(new Bomb(diver.X, diver.Y));
                coolDown = 200;
            }
        }

        public void Draw(Graphics graphics, Diver diver)
        {
            graphics.Begin();

            graphics.End();
        }

    }
}
