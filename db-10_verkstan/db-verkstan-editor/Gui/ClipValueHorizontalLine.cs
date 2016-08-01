using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace VerkstanEditor.Gui
{
    public partial class ClipValueHorizontalLine : UserControl
    {
        #region Properties
        private int beatWidth = 31;
        public int BeatWidth
        {
            get
            {
                return beatWidth;
            }
            set
            {
                beatWidth = value;
                Invalidate();
            }
        }
        #endregion

        #region Constructors
        public ClipValueHorizontalLine()
        {
            InitializeComponent();
        }
        #endregion

        #region Event Handlers
        private void ClipValueHorizontalLine_Paint(object sender, PaintEventArgs e)
        {
            Brush b = new SolidBrush(ForeColor);
            Pen p = new Pen(Color.FromArgb(100, 100, 100), 1);
            int beats = Width / beatWidth + 1;
            for (int i = 0; i < beats; i++)
            {
                Rectangle beatRectangle = new Rectangle(i * beatWidth, 0, beatWidth, Size.Height);
                if (!e.ClipRectangle.IntersectsWith(beatRectangle))
                    continue;

                if (i % 4 == 0)
                {
                    e.Graphics.DrawLine(p, new Point(i * beatWidth, 0), new Point(i * beatWidth, Height - 1));
                    String number = "" + (i / 4 + 1);
                    SizeF stringSize = e.Graphics.MeasureString(number, Font);
                    if (stringSize.Width < beatWidth)
                        e.Graphics.DrawString(number, Font, b, new Point(i * BeatWidth + 1, 0));
                }
                else
                {
                    e.Graphics.DrawLine(p, new Point(i * beatWidth, Height - 5), new Point(i * beatWidth, Height - 1));
                }
            }
            p.Dispose();
            b.Dispose();
        }
        #endregion
    }
}
