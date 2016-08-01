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
    public partial class ClipValueVerticalLine : UserControl
    {
        #region Constructors
        public ClipValueVerticalLine()
        {
            InitializeComponent();
        }
        #endregion

        #region Event Handlers
        private void ClipValueVerticalLine_Paint(object sender, PaintEventArgs e)
        {
            Brush b = new SolidBrush(ForeColor);
            Pen p = new Pen(Color.FromArgb(100, 100, 100), 1);
            for (int i = 1; i < 10; i++)
            {
                Rectangle rect = new Rectangle(0, i * Height / 10, Size.Width, 1);

                String number = "";
                if (i == 5)
                    number = "0";
                else if (i < 5)
                    number = "" + (1.0f - i / 5.0f);
                else if (i > 5)
                    number = "-" + ((i - 5.0f) / 5.0f);
                SizeF size = e.Graphics.MeasureString(number, Font);
                e.Graphics.DrawString(number, Font, b, Width - 5 - size.Width, rect.Y - size.Height / 2);
                e.Graphics.DrawLine(p, rect.X + rect.Width - 5, rect.Y, rect.X + rect.Width, rect.Y);
            }
            p.Dispose();
            b.Dispose();
        }
        #endregion
    }
}
