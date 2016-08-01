using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using DB.Gui;

namespace DB.DoF.Entities
{
    public class Explodable: PersistentEntity
    {
        SpriteGrid animationGrid;
        int frameCounter = 0;
        int animationFrame = 0;
        int health = 5;

        public Explodable(int x, int y)
        {
            this.X = x * 16;
            this.Y = y * 16;
            Width = 16;
            Height = 16;
            animationGrid = new SpriteGrid("explodable", 6, 1);
            this.IsSolid = true;
        }

        protected override string[] GetConstructorArguments()
        {
            return new string[] {(X / 16).ToString(), (Y / 16).ToString()};
        }

        public override void Draw(Graphics g, GameTime gameTime, Room.Layer layer)
        {
            if (layer == Room.Layer.Player)
            {
                g.Begin();
                animationGrid.Draw(g, Position, health);
                g.End();
            }
        }

        public override void Update(State s, Room room)
        {
            if (health <= 0)
            {
                for (int i = 0; i < 20; i++)
                {
                    room.AddEntity(Particle.Debri(new Point(X + Width / 2, Y + Height / 2)));
                }

                room.RemoveEntity(this);
            }

            base.Update(s, room);
        }

        public override void OnMessageReceived(string channel, string message, object obj)
        {
            if (channel != "explosion")
            {
                return;
            }

            Bomb bomb = (Bomb)obj;
            health -= (int)bomb.CalculateImpact(this);
        }
    }
}
