using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using System.Drawing.Design;
using VerkstanEditor.Logic;

namespace VerkstanEditor.Gui
{
    [ToolboxItem(true)]
    public partial class BeatPositionLine : UserControl
    {
        #region Private Variables
        private int tick;
        private bool dragTick = false;
        #endregion

        #region Properties
        private int beatWidth = 16;
        public int BeatWidth
        {
            set
            {
                beatWidth = value;
                Refresh();
            }
            get
            {
                return beatWidth;
            }

        }
        #endregion

        #region Constructor
        public BeatPositionLine()
        {
            InitializeComponent();
            Metronome.BeatChangedSlowUpdate += new Metronome.BeatChangedHandler(this.BeatPositionLine_BeatChangedSlowUpdate);
        }
        #endregion

        #region Event Handlers
        public void BeatPositionLine_BeatChangedSlowUpdate(int tick)
        {
            int oldBeatInPixels = (int)(beatWidth * (this.tick / (float)Metronome.TicksPerBeat));
            int newBeatInPixels = (int)(beatWidth * (tick / (float)Metronome.TicksPerBeat));
            this.tick = tick;

            int x = 0;
            int width = 0;
            if (oldBeatInPixels < newBeatInPixels)
            {
                x = oldBeatInPixels;
                width = newBeatInPixels - oldBeatInPixels + 1;
            }
            else
            {
                x = newBeatInPixels;
                width = oldBeatInPixels - newBeatInPixels + 1;
            }

            Invalidate(new Rectangle(x, 0, width, Size.Height), false);
        }
        private void BeatPositionLine_Paint(object sender, PaintEventArgs e)
        {
            Brush b = new SolidBrush(ForeColor);
            Pen p = new Pen(Color.FromArgb(100, 100, 100), 1);
            int beats = Width / beatWidth + 1;
            for (int i = 0; i < beats; i++)
            {
                Rectangle beatRectangle = new Rectangle(i * beatWidth, 0, beatWidth, Size.Height);
                if (!e.ClipRectangle.IntersectsWith(beatRectangle))
                    continue;

                if (i % 2 == 0)
                {
                    e.Graphics.DrawLine(p, new Point(i * beatWidth, 0), new Point(i * beatWidth, Height - 1));
                    String number = "" + (i + 1);
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

            int tickInPixels = (int)(beatWidth * (tick / (float)Metronome.TicksPerBeat));
            e.Graphics.DrawLine(Pens.Red, new Point(tickInPixels, 0), new Point(tickInPixels, Height));

            //Rectangle loopStartRectangle = new Rectangle(Metronome.LoopStart / Metronome.TicksPerBeat * beatWidth, 0, 2, Height);
            //if (!e.ClipRectangle.IntersectsWith(loopStartRectangle))
            //    return;

           // e.Graphics.DrawLine(Pens.Blue, loopStartRectangle.X, 0, loopStartRectangle.X, Height);
           // e.Graphics.DrawLine(Pens.Blue, loopStartRectangle.X + 1, 0, loopStartRectangle.X + 1, Height);

           // Rectangle loopEndRectangle = new Rectangle(Metronome.LoopEnd / Metronome.TicksPerBeat * beatWidth, 0, 2, Height);
           // if (!e.ClipRectangle.IntersectsWith(loopEndRectangle))
           //     return;

           // e.Graphics.DrawLine(Pens.Blue, loopEndRectangle.X, 0, loopEndRectangle.X, Height);
           
            //e.Graphics.DrawLine(Pens.Blue, loopEndRectangle.X + 1, 0, loopEndRectangle.X + 1, Height);    
        }
        private void BeatPositionLine_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                if (e.X % beatWidth > beatWidth / 2)
                    Metronome.Tick = (e.X / beatWidth + 1) * Metronome.TicksPerBeat;
                else
                    Metronome.Tick = (e.X / beatWidth) * Metronome.TicksPerBeat;
                dragTick = true;
            }
        }
        private void BeatPositionLine_MouseMove(object sender, MouseEventArgs e)
        {
            if (!dragTick)
                return;

            Metronome.Tick = e.X / beatWidth * Metronome.TicksPerBeat;
        }
        private void BeatPositionLine_MouseUp(object sender, MouseEventArgs e)
        {
            dragTick = false;
        }
        #endregion
    }
}
