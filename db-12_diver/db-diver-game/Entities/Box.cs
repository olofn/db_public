using System;
using System.Collections.Generic;
using System.Text;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace DB.DoF.Entities
{
    public class Box : PersistentEntity
    {
        Texture2D texture;
        int Weight;

        public Box(string texture, int x, int y, int weight)
        {
            this.texture = DiverGame.DefaultContent.Load<Texture2D>(texture);
            this.texture.Name = texture;
            this.Weight = weight;
            this.X = x;
            this.Y = y;
            this.Width = this.texture.Width;
            this.Height = this.texture.Height;
            this.IsTransitionable = true;
            this.IsSolid = true;
        }

        public override bool IsUpdateNeeded(Room room)
        {
            return !IsTileSolidBelow(room);
        }

        protected override string[] GetConstructorArguments()
        {
            return new string[] { Quote(texture.Name), X.ToString(), Y.ToString(), Weight.ToString() };
        }

        public override void Draw(DB.Gui.Graphics g, Microsoft.Xna.Framework.GameTime gameTime, Room.Layer layer)
        {
            if (layer == Room.Layer.Player)
            {
                g.Begin();
                g.Draw(texture, Position, Color.White);
                g.End();
            }
        }

        public override void Update(State s, Room room)
        {
            if (room.Diver != null)
            {
                Rectangle d = room.Diver.Dimension;
                d.Inflate(1, 0);
                if (d.Intersects(Dimension))
                {
                    if (Math.Sign(Center.X - room.Diver.Center.X) == Math.Sign(room.Diver.AppliedForce.X))
                    {
                        Velocity.X += (Resolution / Weight) * Math.Sign(room.Diver.AppliedForce.X) * Math.Max(Math.Abs(room.Diver.AppliedForce.X) - Weight, 0);
                    }
                }
            }

            Velocity.Y = 200;
            Velocity.X = (int)(Velocity.X * 0.5f);
            MoveWithCollision(room);
        }
    }
}
