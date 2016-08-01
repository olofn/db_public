using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace DB.Gui
{
    public abstract class Box
    {
        public abstract void Draw(Graphics g, Rectangle dest);

        public void Draw(Graphics g, Point size)
        {
            Draw(g, new Rectangle(0, 0, size.X, size.Y));
        }
    }
}
