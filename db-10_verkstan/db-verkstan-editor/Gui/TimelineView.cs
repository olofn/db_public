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
    public partial class TimelineView : UserControl
    {
        #region Properties
        public Clip ViewedClip
        {
            get
            {
                return timelineChannelsView1.ViewedClip;
            }
            set
            {
                timelineChannelsView1.ViewedClip = value;
            }
        }
        private Timeline timeline;
        public Timeline Timeline
        {
            set
            {
                if (timeline != value)
                {
                    timeline = value;
                    timelineChannelsView1.Timeline = value;
                    timelineChannelsPropertiesView1.Timeline = value;

                    if (timeline != null)
                    {
                        Metronome.Tick = 0;
                        Metronome.Ticks = timeline.GetTicks();

                    }
                    else
                    {
                        Metronome.Tick = 0;
                        Metronome.Ticks = 0;
                    }
                }
            }
            get
            {
                return timeline;
            }
        }
        public TimelineChannelsView.Modes Mode
        {
            set
            {
                timelineChannelsView1.Mode = value;
            }
            get
            {
                return timelineChannelsView1.Mode;
            }
        }
        #endregion

        #region Constructors
        public TimelineView()
        {
            InitializeComponent();
            this.MouseWheel += new MouseEventHandler(Timeline_MouseWheel);
            numericUpDown1.Value = timelineChannelsView1.BeatWidth;
        }
       
        #endregion

        #region Event Handlers
        private void contextMenuStrip1_Opening(object sender, CancelEventArgs e)
        {
            if (timeline == null)
            {
                addChannelToolStripMenuItem.Enabled = false;
                removeChannelToolStripMenuItem.Enabled = false;
            }
            else
            {
                addChannelToolStripMenuItem.Enabled = true;
                removeChannelToolStripMenuItem.Enabled = timeline.GetSelectedChannel() != null;
            }
        }
        private void addChannelToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (timeline != null)
                timeline.AddChannel(new Channel());
        }
        private void removeChannelToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (timeline != null)
                timeline.RemoveSelectedChannel();
        }
        private void timelineChannels1_Resize(object sender, EventArgs e)
        {
            UpdateScrollBars();
            beatPositionLine1.Width = timelineChannelsView1.Width;
        }
        private void timelineChannels1_Load(object sender, EventArgs e)
        {
            UpdateScrollBars();
        }
        private void hScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            timelineChannelsView1.Left = -e.NewValue;
            beatPositionLine1.Left = -e.NewValue;
        }
        private void vScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            timelineChannelsView1.Top = -e.NewValue;
            timelineChannelsPropertiesView1.Top = -e.NewValue;
        }
        private void Timeline_MouseWheel(object sender, MouseEventArgs e)
        {
            if (e.Delta > 0)
            {
                if (vScrollBar1.Value - vScrollBar1.SmallChange > vScrollBar1.Minimum)
                    vScrollBar1.Value -= vScrollBar1.SmallChange;
                else
                    vScrollBar1.Value = vScrollBar1.Minimum;
            }
            else
            {
                if (vScrollBar1.Value + vScrollBar1.SmallChange < (vScrollBar1.Maximum - vScrollBar1.LargeChange + 1))
                    vScrollBar1.Value += vScrollBar1.SmallChange;
                else
                    vScrollBar1.Value = vScrollBar1.Maximum - vScrollBar1.LargeChange + 1;
            }

            timelineChannelsView1.Top = -vScrollBar1.Value;
            timelineChannelsPropertiesView1.Top = -vScrollBar1.Value;
        }
        private void splitPositionAndChannels_Panel2_Resize(object sender, EventArgs e)
        {
            UpdateScrollBars();
        }
        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            timelineChannelsView1.BeatWidth = Convert.ToInt32(numericUpDown1.Value);
            beatPositionLine1.BeatWidth = Convert.ToInt32(numericUpDown1.Value);
        }
        private void timelineChannelsView1_ViewedClipChanged(object sender, EventArgs e)
        {
            OnViewedClipChanged();
        }
        #endregion

        #region Private Methods
        private void UpdateScrollBars()
        {
            hScrollBar1.Enabled = timelineChannelsView1.Width > splitPositionAndChannels.Panel2.Width;
            vScrollBar1.Enabled = timelineChannelsView1.Height > splitPositionAndChannels.Panel2.Height;

            hScrollBar1.Minimum = 0;
            hScrollBar1.Maximum = timelineChannelsView1.Width;
            hScrollBar1.LargeChange = splitPositionAndChannels.Panel2.Width;
            hScrollBar1.SmallChange = 10;
          
            vScrollBar1.Minimum = 0;
            vScrollBar1.Maximum = timelineChannelsView1.Height;
            vScrollBar1.LargeChange = splitPositionAndChannels.Panel2.Height;
            vScrollBar1.SmallChange = 10;

            if (!hScrollBar1.Enabled)
            {
                timelineChannelsView1.Left = 0;
                beatPositionLine1.Left = 0;
            }

            if (!vScrollBar1.Enabled)
            {
                timelineChannelsView1.Top = 0;
                timelineChannelsPropertiesView1.Top = 0;
            }
        }
        #endregion

        #region Events
        public event EventHandler ViewedClipChanged;
        protected void OnViewedClipChanged()
        {
            if (ViewedClipChanged != null)
                ViewedClipChanged(this, new EventArgs());
        }
        #endregion
    }
}
