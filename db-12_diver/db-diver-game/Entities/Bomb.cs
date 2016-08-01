using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using DB.Gui;

namespace DB.DoF.Entities
{
    public class Bomb: Entity
    {
        SpriteGrid animationGrid;
        int frameCounter = 0;
        int animationFrame = 0;
        public int Power = 40;

        public Bomb(int x, int y)
        {
            this.X = x;
            this.Y = y;
            Width = 16;
            Height = 16;
            animationGrid = new SpriteGrid("bomb", 3, 1);
        }

        public override void Draw(Graphics g, GameTime gameTime, Room.Layer layer)
        {
            if (layer == Room.Layer.Player)
            {
                g.Begin();
                animationGrid.Draw(g, Position, animationFrame);
                g.End();
            }
        }

        public float CalculateImpact(Entity e)
        {
            Vector2 bv = new Vector2(X, Y);
            Vector2 ev = new Vector2(e.X, e.Y);
            Vector2 d = bv - ev;
            float distance = (d.Length() / 16.0f);

            return Power / (float)(Math.Pow(2, distance));
        }

        public override void Update(State s, Room room)
        {
            frameCounter++;


            if (frameCounter >= 200)
            {
                room.Broadcast("explosion", "", this);

                for (int i = 0; i < 10; i++)
                {
                    room.AddEntity(Particle.MakeBigBubble(new Point(X + Width / 2, Y)));
                    room.AddEntity(Particle.MakeSmallBubble(new Point(X + Width / 2, Y)));
                    room.AddEntity(Particle.MakeTinyBubble(new Point(X + Width / 2, Y)));
                }
                
                for (int i = 0; i < 20; i++)
                {
                    room.AddEntity(Particle.Debri(new Point(X + Width / 2, Y + Height / 2)));
                }
                
                room.AddEntity(Particle.ExplosionGlow(Center));
                room.AddEntity(Particle.ExplosionGlow(Center));
                room.AddEntity(Particle.ExplosionGlow(Center));
                room.AddEntity(Particle.ExplosionGlow(Center));
                room.AddEntity(Particle.ExplosionGlow(Center));
                room.AddEntity(Particle.ExplosionGlow(Center));

                room.RemoveEntity(this);
            }

            if (frameCounter % 5 == 0)
            {
                animationFrame++;
            }

            if (frameCounter % 20 == 0)
            {
                room.AddEntity(Particle.MakeTinyBubble(new Point(X + Width / 2, Y)));
            }

            Velocity.Y = 2 * Resolution;
            MoveWithCollision(room);

           base.Update(s, room);
        }
    }
}
