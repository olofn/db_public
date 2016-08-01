using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace DB.Gui.Boxes
{
    public class BorderBox : Box
    {
        Texture2D texture;
        int paddingLeft, paddingRight, paddingTop, paddingBottom;
        bool stretched;
        Color color;
        Color border;

        public BorderBox(Texture2D texture, bool stretched, Color color, Color border)
            : this(texture, stretched, color, border, 0, 0, 0, 0)
        {
        }

        public BorderBox(Texture2D texture, bool stretched, Color color, Color border, int padding)
            : this(texture, stretched, color, border, padding, padding, padding, padding)
        {
        }

        public BorderBox(Texture2D texture, bool stretched, Color color, Color border, int xPadding, int yPadding)
            : this(texture, stretched, color, border, yPadding, xPadding, yPadding, xPadding)
        {
        }

        public BorderBox(Texture2D texture, bool stretched, Color color, Color border, int paddingLeft, int paddingRight, int paddingTop, int paddingBottom)
        {
            this.texture = texture;
            this.stretched = stretched;
            this.paddingLeft = paddingLeft;
            this.paddingRight = paddingRight;
            this.paddingTop = paddingTop;
            this.paddingBottom = paddingBottom;
            this.color = color;
            this.border = border;
        }

        public override void Draw(Graphics g, Rectangle dest)
        {
            if (stretched)
            {
                DrawStreched(g, dest);
            }
            else
            {
                DrawTiled(g, dest);
            }
        }

        void DrawStreched(Graphics g, Rectangle dest)
        {
            g.Draw(texture, new Rectangle(dest.X, dest.Y, paddingLeft, paddingTop),
                            new Rectangle(0, 0, paddingLeft, paddingTop), border);
            
            g.Draw(texture, new Rectangle(dest.X + paddingLeft, dest.Y, dest.Width - paddingLeft - paddingRight, paddingTop), 
                            new Rectangle(paddingLeft, 0, texture.Width - paddingLeft - paddingRight, paddingTop), border);
            
            g.Draw(texture, new Rectangle(dest.X + dest.Width - paddingRight, dest.Y, paddingLeft, paddingTop),
                            new Rectangle(texture.Width - paddingRight, 0, paddingLeft, paddingTop), border);
            
            
            g.Draw(texture, new Rectangle(dest.X, dest.Y + paddingTop, paddingLeft, dest.Height - paddingTop - paddingBottom),
                            new Rectangle(0, paddingTop, paddingLeft, texture.Height - paddingTop - paddingBottom), border);

            g.Draw(texture, new Rectangle(dest.X + paddingLeft, dest.Y + paddingTop, dest.Width - paddingLeft - paddingRight, dest.Height - paddingTop - paddingBottom),
                            new Rectangle(paddingLeft, paddingTop, texture.Width - paddingLeft - paddingRight, texture.Height - paddingLeft - paddingRight), color);

            g.Draw(texture, new Rectangle(dest.X + dest.Width - paddingRight, dest.Y + paddingTop, paddingRight, dest.Height - paddingTop - paddingBottom),
                            new Rectangle(texture.Width - paddingRight, paddingTop, paddingRight, texture.Height - paddingTop - paddingBottom), border);


            g.Draw(texture, new Rectangle(dest.X, dest.Y + dest.Height - paddingBottom, paddingLeft, paddingBottom),
                            new Rectangle(0, texture.Height - paddingBottom, paddingLeft, paddingBottom), border);

            g.Draw(texture, new Rectangle(dest.X + paddingLeft, dest.Y + dest.Height - paddingBottom, dest.Width - paddingLeft - paddingRight, paddingBottom),
                            new Rectangle(paddingLeft, texture.Height - paddingBottom, texture.Width - paddingLeft - paddingRight, paddingBottom), border);

            g.Draw(texture, new Rectangle(dest.X + dest.Width - paddingRight, dest.Y + dest.Height - paddingBottom, paddingLeft, paddingBottom),
                            new Rectangle(texture.Width - paddingRight, texture.Height - paddingBottom, paddingLeft, paddingBottom), border);
        }

        void DrawTiled(Graphics g, Rectangle dest)
        {
            // TODO
        }
    }
}
