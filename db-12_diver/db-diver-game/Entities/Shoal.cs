using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;

namespace DB.DoF.Entities
{
    public class Fishy : Entity
    {
        public float TargetX, TargetY;
        float x, y;
        float speedX, speedY;
        float rotation;
        Color color;

        SpriteGrid animationGrid;
        double animationGridFrame;
        int sprites;

        public Fishy(string spriteGridName, Color color, int sprites, int x, int y)
        {
            this.color = color;
            TargetX = x;
            TargetY = y;
            this.x = y;
            this.y = x;
            X = (int)this.x;
            Y = (int)this.y;

            this.sprites = sprites;
            animationGrid = new SpriteGrid(spriteGridName, sprites, 1);
            Width = animationGrid.FrameSize.X;
            Height = animationGrid.FrameSize.Y;
        }

        public override void Draw(DB.Gui.Graphics g, GameTime gameTime, Room.Layer layer)
        {

            animationGrid.Draw(g, Position, ((int)animationGridFrame) % sprites, rotation, color);
        }

        public override void Update(State s, Room room)
        {
            base.Update(s, room);
            Vector2 direction = new Vector2((float)((TargetX - x) * (DiverGame.Random.NextDouble() * 0.2f + 0.8f)), 
                                            (float)((TargetY - y) * (DiverGame.Random.NextDouble() * 0.2f + 0.8f)));



            if(direction.LengthSquared() > 0)
                direction.Normalize();

            speedX += direction.X * 0.007f;
            speedY += direction.Y * 0.007f;
            speedX *= 0.999f;
            speedY *= 0.999f;

            float speed = (float)Math.Sqrt(speedX * speedX + speedY * speedY);
            animationGridFrame += speed * 0.25f + 0.03f;

            x += speedX;
            y += speedY;
            X = (int)x;
            Y = (int)y;

            float desiredRot = (float)Math.Atan2(speedX, -speedY) - (float)Math.PI / 2f;
            float rotDiff = desiredRot - rotation;
            while (rotDiff > MathHelper.Pi) rotDiff -= MathHelper.TwoPi;
            while (rotDiff < -MathHelper.Pi) rotDiff += MathHelper.TwoPi;
            rotation += rotDiff * 0.1f;
        }
    }

    public class Shoal : Entity
    {
        SmoothFloat targetX = new SmoothFloat(0f, 0.8f);
        SmoothFloat targetY = new SmoothFloat(0f, 0.8f);

        IList<Fishy> fishies = new List<Fishy>();

        public Shoal(Color color)
        {
            targetX.Target = 100;
            targetY.Target = 100;
            
            for(int i = 0; i < 100; i++)
                fishies.Add(new Fishy("small_fish", color, 4, (int)targetX.Value + DiverGame.Random.Next(80) - 40, (int)targetY.Value + DiverGame.Random.Next(80) - 40));

            foreach (Fishy fish in fishies)
            {
                fish.TargetX = targetX.Value + DiverGame.Random.Next(40) - 80;
                fish.TargetY = targetY.Value + DiverGame.Random.Next(40) - 80;
            }
        }

        public override void Draw(DB.Gui.Graphics g, Microsoft.Xna.Framework.GameTime gameTime, Room.Layer layer)
        {
            if (layer == Room.Layer.Background)
            {
                g.Begin();

                foreach (Fishy fish in fishies)
                {
                    fish.Draw(g, gameTime, layer);
                }
                g.End();
            }
        }

        public override void Update(State s, Room room)
        {
            base.Update(s, room);
            if (DiverGame.Random.Next(400) == 0)
            {
                targetX.Target = DiverGame.Random.Next(room.TileMap.SizeInPixels.X);
                targetY.Target = DiverGame.Random.Next((int)(room.TileMap.SizeInPixels.Y*0.8));
            }

            targetX.Update();
            targetY.Update();
            foreach (Fishy fish in fishies)
            {
                fish.TargetX = targetX.Value + DiverGame.Random.Next(40) - 80;
                fish.TargetY = targetY.Value + DiverGame.Random.Next(40) - 80;
                fish.Update(s, room);
            }
        }
    }
}
