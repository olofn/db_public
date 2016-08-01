using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework.Graphics;

namespace DB.DoF.Entities
{
    public class Button : Entity
    {
        SpriteGrid spriteGrid;
        public Boolean Pressed;
        String id;

        public Button(int x, int y, String id)
        {
            spriteGrid = new SpriteGrid("button", 2, 1);
            this.id = id;
            X = x*16;
            Y = y*16 + 16 - 5;
            this.Width = spriteGrid.FrameSize.X;
            this.Height = 7;
        }

        public override void Draw(DB.Gui.Graphics g, Microsoft.Xna.Framework.GameTime gameTime, Room.Layer layer)
        {
            g.Begin();
            spriteGrid.Draw(g, Position, Pressed ? 1 : 0);
            //g.Draw(DiverGame.White, Dimension, Color.Red);
            g.End();
        }

        public override void Update(State s, Room room)
        {

            bool pushed = false;

            foreach (Entity entity in room.GetCollidingEntities(this))
            {
                if (entity == room.Diver)
                {
                    pushed = true;
                }
            }

            if (pushed && !Pressed)
            {
                room.Broadcast("buttondown", id, this);
                this.Pressed = true;
            }

            if (!pushed && Pressed)
            {
                room.Broadcast("buttonup", id, this);
                this.Pressed = false;
            }
        }
    }
}
