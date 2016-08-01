using System;
using System.Collections.Generic;
using System.Text;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

using DB.Gui;

namespace DB.DoF.Entities
{
    public class Particle : Entity
    {
        SpriteGrid spriteGrid;
        float framerate;
        Vector2 position;
        Vector2 velocity;
        Vector2 gravity;
        float damping;
        Color color;
        SpriteBlendMode blend;
        Room.Layer layer;
        float frame;
        int timeToLive;

        public Particle(SpriteGrid spriteGrid, float framerate, Vector2 position, Vector2 velocity, Vector2 gravity, float damping, Color color, SpriteBlendMode blend, Room.Layer layer, float scale, int timeToLive)
        {
            this.spriteGrid = spriteGrid;
            this.framerate = framerate;
            this.position = position;
            this.velocity = velocity;
            this.gravity = gravity;
            this.damping = damping;
            this.color = color;
            this.blend = blend;
            this.layer = layer;
            this.timeToLive = timeToLive;

            CleanUpOnRoomLeft = true;

            Width = (int)(scale * spriteGrid.FrameSize.X);
            Height = (int)(scale * spriteGrid.FrameSize.Y);

            this.position.X -= Width / 2.0f;
            this.position.Y -= Height / 2.0f;

            X = (int)this.position.X;
            Y = (int)this.position.Y;
        }

        public static Particle MakeBigBubble(Point pos)
        {
            SpriteGrid spriteGrid = new SpriteGrid("bubble", 4, 1);
            Random r = DiverGame.Random;
            return new Particle(spriteGrid,
                                0.6f * (float)r.NextDouble() * 0.5f,
                                new Vector2((float)pos.X, (float)pos.Y),
                                new Vector2(((float)r.NextDouble() - 0.5f) * 3.0f, (float)-r.NextDouble() * 1.5f),
                                new Vector2(0, -(float)r.NextDouble() * 0.2f - 0.2f),
                                0.9f,
                                new Color(255, 255, 255, 128),
                                SpriteBlendMode.AlphaBlend,
                                Room.Layer.Background,
                                1.0f, -1);
        }

        public static Particle MakeSmallBubble(Point pos)
        {
            SpriteGrid spriteGrid = new SpriteGrid("bubblesmall", 1, 1);
            Random r = DiverGame.Random;
            return new Particle(spriteGrid,
                                1.0f,
                                new Vector2((float)pos.X, (float)pos.Y),
                                new Vector2(((float)r.NextDouble() - 0.5f) * 3.0f, (float)-r.NextDouble() * 1.5f),
                                new Vector2(0, -(float)r.NextDouble() * 0.2f - 0.1f),
                                0.9f,
                                new Color(255, 255, 255, 96),
                                SpriteBlendMode.AlphaBlend,
                                Room.Layer.Background,
                                1.0f, -1);
        }


        public static Particle MakeTinyBubble(Point pos)
        {
            SpriteGrid spriteGrid = new SpriteGrid("bubbletiny", 1, 1);
            Random r = DiverGame.Random;
            return new Particle(spriteGrid,
                                10.0f,
                                new Vector2((float)pos.X, (float)pos.Y),
                                new Vector2(((float)r.NextDouble() - 0.5f) * 3.0f, (float)-r.NextDouble() * 1.5f),
                                new Vector2(0, -(float)r.NextDouble() * 0.1f - 0.07f),
                                0.9f,
                                new Color(255, 255, 255, 64),
                                SpriteBlendMode.AlphaBlend,
                                Room.Layer.Background,
                                1.0f, -1);
        }

        public static Particle MakeSpark(Point pos)
        {
            SpriteGrid spriteGrid = new SpriteGrid("glow", 1, 1);
            Random r = DiverGame.Random;
            return new Particle(spriteGrid,
                                1.0f,
                                new Vector2((float)pos.X, (float)pos.Y),
                                new Vector2(0, 0),
                                new Vector2(0, -(float)r.NextDouble() * 0.1f - 0.07f),
                                0.9f,
                                new Color(255, 255, 255, 255),
                                SpriteBlendMode.Additive,
                                Room.Layer.Player,
                                0.015f, 20);
        }

        public static Particle ExplosionDust(Point pos)
        {
            SpriteGrid spriteGrid = new SpriteGrid("glow", 1, 1);
            Random r = DiverGame.Random;
            return new Particle(spriteGrid,
                                1.0f,
                                new Vector2((float)pos.X, (float)pos.Y),
                                new Vector2(((float)r.NextDouble() - 0.5f) * 3.0f, 0),
                                new Vector2(0, 0),
                                0.9f,
                                new Color(255, 255, 255, 255),
                                SpriteBlendMode.Additive,
                                Room.Layer.Player,
                                0.2f,
                                50);
        }

        public static Particle Debri(Point pos)
        {
            SpriteGrid spriteGrid = new SpriteGrid("debri", 4, 1);
            Random r = DiverGame.Random;
            return new Particle(spriteGrid,
                                1.0f,
                                new Vector2((float)pos.X, (float)pos.Y),
                                new Vector2(((float)r.NextDouble() - 0.5f) * 50, ((float)r.NextDouble() - 0.5f) * 50),
                                new Vector2(0.0f,1.0f),
                                0.8f,
                                Color.White,
                                SpriteBlendMode.AlphaBlend,
                                Room.Layer.Player,
                                1.0f, 
                                40);
        }

        public static Particle ExplosionGlow(Point pos)
        {
            SpriteGrid spriteGrid = new SpriteGrid("glow", 1, 1);
            Random r = DiverGame.Random;
            return new Particle(spriteGrid,
                                1.0f,
                                new Vector2((float)pos.X, (float)pos.Y),
                                new Vector2(0,0),
                                new Vector2(0,0),
                                1.0f,
                                Color.Tomato,
                                SpriteBlendMode.Additive,
                                Room.Layer.Foreground,
                                0.5f,
                                8);
        }

        public override void Draw(Graphics g, GameTime gameTime, Room.Layer layer)
        {
            if (layer == this.layer)
            {
                Color c = color;

                if (timeToLive > 0)
                {
                    c = new Color(c.R, c.G, c.B, (byte)(color.A * (1.0f - (frame / timeToLive))));
                }

                g.Begin(blend);
                spriteGrid.Draw(g, Dimension, (int)frame, c);
                g.End();
            }
        }

        public override void Update(State s, Room room)
        {
            position += velocity;
            velocity += gravity;
            velocity *= damping;
            frame += framerate;
            X = (int)position.X;
            Y = (int)position.Y;

            if (timeToLive <= 0 && !new Rectangle(0, 0, room.Size.X, room.Size.Y).Intersects(Dimension))
            {
                room.RemoveEntity(this);
            }

            if (timeToLive > 0 && frame > timeToLive)
            {
                room.RemoveEntity(this);
            }
        }
    }
}
