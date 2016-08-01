using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using VerkstanEditor.Logic;

namespace VerkstanEditor.Gui
{
    [ToolboxItem(true)]
    public partial class MiniTimeline : UserControl
    {
        #region Private Variables
        private bool dragTick = false;
        private int tick;
        #endregion

        #region Constructor
        public MiniTimeline()
        {
            InitializeComponent();
            DoubleBuffered = true;
            Metronome.BeatChangedSlowUpdate += new Metronome.BeatChangedHandler(this.MiniTimeline_BeatChangedSlowUpdate);
        }
        #endregion

        #region Event Handlers
        public void MiniTimeline_BeatChangedSlowUpdate(int tick)
        {
            this.tick = tick;
            Refresh();
        }
        private void MiniTimeline_Paint(object sender, PaintEventArgs e)
        {
        
            Pen p = new Pen(ForeColor, 1);
            float beatPosition = this.tick / (float)Metronome.Ticks; 
            int beatInPixels = (int)((Size.Width - 1) * beatPosition);
            e.Graphics.DrawLine(p, new Point(beatInPixels, 0), new Point(beatInPixels, Size.Height));
            p.Dispose();
        }
        private void MiniTimeline_MouseDown(object sender, MouseEventArgs e)
        {
            
            if (e.Button != MouseButtons.Left)
                return;

            float beatPosition = e.X / (float)(Size.Width - 1);
            Metronome.Tick = (int)(Metronome.Ticks * beatPosition);

            dragTick = true;
        }
        private void MiniTimeline_MouseMove(object sender, MouseEventArgs e)
        {
            
            if (!dragTick)
                return;

            float beatPosition = e.X / (float)(Size.Width - 1);
            Metronome.Tick = (int)(Metronome.Ticks * beatPosition);
           
        }
        private void MiniTimeline_MouseUp(object sender, MouseEventArgs e)
        {
            dragTick = false;
        }
        #endregion
    }
}
