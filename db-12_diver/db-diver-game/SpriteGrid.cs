using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace DB.DoF
{
    public class SpriteGrid
    {
        Texture2D texture;
        public int XCount;
        public int YCount;
        public Point FrameSize { get { return new Point(texture.Width / XCount, texture.Height / YCount); } }

        public SpriteGrid(Texture2D texture, int xCount, int yCount)
        {
            this.texture = texture;
            this.XCount = xCount;
            this.YCount = yCount;
        }

        public SpriteGrid(string filename, int xCount, int yCount)
            :this(DiverGame.DefaultContent.Load<Texture2D>(filename), xCount, yCount)
        {
            
        }

        public void Draw(Gui.Graphics g, Point position, int frame, SpriteEffects spriteEffects)
        {
            g.Draw(texture, new Vector2(position.X, position.Y), GetRectangle(frame), Color.White, 0f, Vector2.Zero, 1f, spriteEffects, 0f);
        }

        public void Draw(Gui.Graphics g, Point position, int frame, float rotation, Color color)
        {
            g.Draw(texture, new Vector2(position.X, position.Y), GetRectangle(frame), color, rotation, new Vector2(FrameSize.X / 2, FrameSize.Y / 2), 1f, SpriteEffects.None, 1f);
        }

        public void Draw(Gui.Graphics g, Point position, int frame, Color color)
        {
            g.Draw(texture, position, GetRectangle(frame), color);
        }

        public void Draw(Gui.Graphics g, Rectangle dim, int frame, Color color)
        {
            g.Draw(texture, dim, GetRectangle(frame), color);
        }

        public void Draw(Gui.Graphics g, Point position, int frame)
        {
            g.Draw(texture, position, GetRectangle(frame), Color.White);
        }

        private Rectangle GetRectangle(int frame)
        {
            return new Rectangle((frame % XCount) * FrameSize.X, ((frame / XCount) % YCount) * FrameSize.Y, FrameSize.X, FrameSize.Y); 
        }
    }
}
