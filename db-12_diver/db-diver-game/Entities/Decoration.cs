using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using DB.Gui;

namespace DB.DoF.Entities
{
    public class Decoration: Entity
    {
        SpriteGrid animationGrid;
        int animationGridFrame;
        int animationSpeed;
        Color color;

        Room.Layer layer;

        public Decoration(SpriteGrid spriteGrid, int animationSpeed, int x, int y, Room.Layer layer)
            :
            this(spriteGrid, animationSpeed, x, y, layer, Color.White)
        { }

        public Decoration(SpriteGrid spriteGrid, int animationSpeed, int x, int y, Room.Layer layer, Color color)
            :
        this(spriteGrid, animationSpeed, new Rectangle(x, y, spriteGrid.FrameSize.X, spriteGrid.FrameSize.Y), layer, color)
        { }

        public Decoration(SpriteGrid spriteGrid, int animationSpeed, Rectangle dimension, Room.Layer layer, Color color)
        {
            X = dimension.X;
            Y = dimension.Y;
            Width = dimension.Width;
            Height = dimension.Height;
            this.layer = layer;
            this.animationSpeed = animationSpeed;
            this.color = color;
            animationGrid = spriteGrid;
        }



        public override void Draw(Graphics g, GameTime gameTime, Room.Layer layer)
        {
            g.Begin();

            if (layer == this.layer)
                animationGrid.Draw(g, Dimension, animationGridFrame, color);

            g.End();
        }

        public override void Update(State s, Room room)
        {
            base.Update(s, room);

            if (animationSpeed != 0 && s.Time.TotalGameTime.Milliseconds % animationSpeed == 0)
            {
                animationGridFrame++;
            }
        }
    }
}
