using System;
using System.Collections.Generic;
using System.Text;

using DB.Gui;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace DB.DoF.Entities
{
    public class Pickup : PersistentEntity
    {
        readonly public ITool Tool;
        string text;
        int startY;

        public Pickup(int x, int y, ITool tool, string text)
        {
            Tool = tool;
            this.text = text;
            X = x;
            startY = Y = y;
            Size = new Point(16, 16);
        }

        protected override string[] GetConstructorArguments()
        {
            return new string[] { X.ToString(), startY.ToString(), "new " + Tool.GetType().Name + "()", Quote(text) };
        }

        public override void Draw(DB.Gui.Graphics g, Microsoft.Xna.Framework.GameTime gameTime, Room.Layer layer)
        {
            if (layer == Room.Layer.Player)
            {
                g.Begin();
                g.Draw(Tool.Icon, Position, Color.White);
                g.End();
            }
        }

        public override void Update(State s, Room room)
        {
            Y = startY + (int)(Math.Sin(s.Time.TotalGameTime.Ticks / 10000000.0f) * 8.5f);
            room.AddEntity(Particle.MakeSpark(new Point(X + DiverGame.Random.Next(Width), Y + DiverGame.Random.Next(Height))));            

            if (room.Diver.Dimension.Intersects(Dimension))
            {
                room.RemoveEntity(this);
                room.Sea.Broadcast("inventory", "add", Tool);
                // Display text
            }
        }
    }
}
