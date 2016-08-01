using System;
using System.Collections.Generic;
using System.Text;

namespace DB.Gui
{
    class Container : Widget
    {
        Box area;

        public Box Area
        {
            get { return area; }
            set { area = value; IsOpaque = area != null; }
        }

        public Container() 
            : this(null)
        {         
        }

        public Container(Box area)
        {
            Area = area;
        }

        public override void Draw(Graphics g, Microsoft.Xna.Framework.GameTime gameTime)
        {
            if (area != null)
            {
                area.Draw(g, Size);
            }
        }
    }
}
