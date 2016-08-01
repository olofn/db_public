using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace DB.Gui.Boxes
{
    public class CompoundBox : Box
    {
        List<Box> boxes;

        public CompoundBox()
        {
            boxes = new List<Box>();
        }

        public CompoundBox(Box b)
        {
            boxes = new List<Box>();
            boxes.Add(b);
        }

        public CompoundBox(Box b1, Box b2)
        {
            boxes = new List<Box>();
            boxes.Add(b1);
            boxes.Add(b2);
        }

        public CompoundBox(Box b1, Box b2, Box b3)
        {
            boxes = new List<Box>();
            boxes.Add(b1);
            boxes.Add(b2);
            boxes.Add(b3);
        }

        public CompoundBox(IEnumerable<Box> boxes)
        {
            this.boxes = new List<Box>(boxes);
        }

        public IList<Box> Boxes
        {
            get { return boxes.AsReadOnly(); }
        }

        public void AddFirst(Box b)
        {
            boxes.Insert(0, b);
        }

        public void AddLast(Box b)
        {
            boxes.Add(b);
        }

        public override void Draw(Graphics g, Rectangle dest)
        {
            foreach (Box b in boxes)
            {
                b.Draw(g, dest);
            }
        }
    }
}
