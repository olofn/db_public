using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using DB.Gui;

namespace DB.DoF.Entities
{
    public class Fish : Entity
    {
        public override int X
        {
            set
            {
                base.X = value;
                this.position.X = X;
            }
        }

        public override int Y
        {
            set
            {
                base.Y = value;
                this.position.Y = Y;
            }
        }
        SpriteGrid animationGrid;
        double animationGridFrame;
        int sprites;
        Room.Layer layer;
        Vector2 position = new Vector2();
        int panicCooldown = 0;
        bool dead = false;

        SmoothFloat xSpeed = new SmoothFloat(0, 0.06f), ySpeed = new SmoothFloat(0, 0.03f);

        public Fish(string spriteGridName, int sprites, int x, int y, Room.Layer layer)
        {
            this.position.X = x*16;
            this.position.Y = y*16;

            TriggerNewSpeedTarget();
            this.layer = layer;
            this.sprites = sprites;
            animationGrid = new SpriteGrid(spriteGridName, sprites, 1);
            Width = animationGrid.FrameSize.X;
            Height = animationGrid.FrameSize.Y;
        }

        public override void Draw(Graphics g, GameTime gameTime, Room.Layer layer)
        {

            g.Begin();
            SpriteEffects spriteEffects = xSpeed.Diff < 0 ? SpriteEffects.FlipHorizontally:SpriteEffects.None;
            
            if(dead)
                spriteEffects |= SpriteEffects.FlipVertically;

            if (layer == Room.Layer.Player)
                animationGrid.Draw(g, Position, ((int)animationGridFrame) % sprites, spriteEffects);

            g.End();
        }


        public override void Update(State s, Room room)
        {
            base.Update(s, room);

            if (dead)
            {
                animationGridFrame = 0;
                if (position.Y < 0)
                {
                    room.RemoveEntity(this);
                }

                if (DiverGame.Random.Next(200) == 0)
                {
                    room.AddEntity(Particle.MakeTinyBubble(new Point(base.X + (xSpeed.Diff > 0 ? Width : 0), base.Y + Height / 2)));
                }
            }
            else
            {
                bool panic = false;
                if (panicCooldown > 0)
                {
                    panicCooldown--;
                    if (panicCooldown == 0)
                        TriggerNewSpeedTarget();
                    else
                        panic = true;
                }

                if ((DiverGame.Random.Next(400) == 0 || (panic && DiverGame.Random.Next(20) == 0)))
                {
                    TriggerNewSpeedTarget();
                }

                animationGridFrame += Math.Abs((xSpeed.Diff)) + 0.1;
            }

            xSpeed.Update();
            ySpeed.Update();

            position.X += xSpeed.Value;
            position.Y += ySpeed.Value;

            base.X = (int)position.X;
            base.Y = (int)position.Y;

            if (position.X < 0 && xSpeed.Target < 0 ||
                position.X > room.TileMap.SizeInPixels.X && xSpeed.Diff > 0) xSpeed.Target *= -1;
            if (position.Y < 0 && ySpeed.Target < 0 ||
                position.Y > room.TileMap.SizeInPixels.Y && ySpeed.Diff > 0) ySpeed.Target *= -1;
        }
        
        private void TriggerNewSpeedTarget()
        {
            float xMax = 0.5f;
            float yMax = 0.3f;
            float xMin = 0.1f;
            float yMin = 0.05f;

            if (panicCooldown != 0)
            {
                xMax = 4f;
                yMax = 2f;
                xMin = 1f;
                yMin = 1f;
            }
            xSpeed.Target = xMin + (float)(DiverGame.Random.NextDouble() * (xMax - xMin));
            ySpeed.Target = yMin + (float)(DiverGame.Random.NextDouble() * (yMax - yMin));

            if (DiverGame.Random.Next(2) == 0) xSpeed.Target *= -1f;
            if (DiverGame.Random.Next(2) == 0) ySpeed.Target *= -1f;

        }

        public override void OnMessageReceived(string channel, string message, object obj)
        {
            if (channel == "explosion" && !dead)
            {
                Bomb bomb = (Bomb)obj;
                float impact = bomb.CalculateImpact(this);
                System.Console.WriteLine("fish damage: " + impact);
                if (impact > 0.5f)
                {
                    if (impact > 5f)
                    {
                        dead = true;
                        xSpeed.Target = 0f;
                        ySpeed.Target = -0.1f;
                    }
                    else
                    {
                        panicCooldown = 150;
                        TriggerNewSpeedTarget();
                    }
                }
            }
        }
    }



}
