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
    public partial class TimelineChannelsPropertiesView : UserControl
    {
        #region Properties
        private int channelPadding = 2;
        private int channelHeight = 31;
        public int ChannelHeight
        {
            set
            {
                channelHeight = value;
            }
            get
            {
                return channelHeight;
            }
        }
        private Timeline timeline;
        public Timeline Timeline
        {
            get
            {
                return timeline;
            }
            set
            {
                if (timeline != null)
                {
                    timeline.ChannelAdded -= channelAddedHandler;
                    timeline.ChannelRemoved -= channelRemovedHandler;
                    timeline.ChannelStateChanged -= channelStateChangedHandler;
                }

                timeline = value;

                if (timeline != null)
                {
                    timeline.ChannelAdded += channelAddedHandler;
                    timeline.ChannelRemoved += channelRemovedHandler;
                    timeline.ChannelStateChanged += channelStateChangedHandler;
                }

                UpdateSize();
                ResetControls();
            }
        }
        #endregion

        #region Private Variables
        private Timeline.EventHandler channelAddedHandler;
        private Timeline.EventHandler channelRemovedHandler;
        private Timeline.EventHandler channelStateChangedHandler;
        #endregion

        #region Constructors
        public TimelineChannelsPropertiesView()
        {
            InitializeComponent();
            channelAddedHandler = new Timeline.EventHandler(this.timeline_ChannelAdded);
            channelRemovedHandler = new Timeline.EventHandler(this.timeline_ChannelRemoved);
            channelStateChangedHandler = new Timeline.EventHandler(this.timeline_ChannelStateChanged); 
        }
        #endregion

        #region Private Methods
        private void UpdateSize()
        {
            if (timeline == null)
            {
                Width = 0;
                Height = 0;
                return;
            }

            Height = timeline.Channels.Count * (channelHeight + 2 * channelPadding) + 1;

            if (Parent == null)           
                return;
            
            Width = Parent.Width;
        }
        private void ResetControls()
        {
            Controls.Clear();

            if (timeline == null)
                return;

            foreach (Channel channel in timeline.Channels)
                AddChannel(channel);
        }
        private void AddChannel(Channel channel)
        {
            TimelineChannelPropertiesView p = new TimelineChannelPropertiesView();
            p.MouseDown += new MouseEventHandler(this.timelineChannelPropertiesView_MouseDown);
            p.Top = channel.Y * (channelPadding * 2 + channelHeight) + channelPadding;
            p.Width = Width;
            p.Left = 0;
            p.Value = channel.ChannelNumber;
            p.BackColor = Color.FromArgb(130, 130, 130);

            Channel c = channel;
            p.ValueChanged += delegate(object o, EventArgs e2)
            {
                c.ChannelNumber = p.Value;
            };

            Controls.Add(p);
            UpdateSize();
        }
        #endregion

        #region Event Handlers
        private void TimelineChannelsPropertiesView_MouseDown(object sender, MouseEventArgs e)
        {
            timeline.SelectChannel(new Point(0, PixelYToBeatY(e.Y)));
        }
        private void timelineChannelPropertiesView_MouseDown(object sender, MouseEventArgs e)
        {
            int y = ((Control)sender).Top + e.Y;
            timeline.SelectChannel(new Point(0, PixelYToBeatY(y)));
        }
        private void ChannelInfos_Load(object sender, EventArgs e)
        {
            UpdateSize();
        }
        private void timeline_ChannelAdded(Timeline.EventArgs e)
        {
            AddChannel(e.Channel);
        }
        private void timeline_ChannelRemoved(Timeline.EventArgs e)
        {
            foreach (Control control in Controls)
            {
                if (PixelYToBeatY(control.Top) == e.Channel.Y)
                {
                    Controls.Remove(control);
                    break;
                }
            }
            
            int i = 0;
            foreach (Channel channel in timeline.Channels)
            {
                if (channel.Y >= e.Channel.Y)
                    Controls[i].Top = channel.Y * (channelPadding * 2 + channelHeight) + channelPadding;
                i++;
            }
            UpdateSize();
        }
        private void timeline_ChannelStateChanged(Timeline.EventArgs e)
        {
            foreach (Control control in Controls)
            {
                if (PixelYToBeatY(control.Top) == e.Channel.Y)
                {
                    if (e.Channel.IsSelected)
                        control.BackColor = Color.FromArgb(200, 200, 200);
                    else
                        control.BackColor = Color.FromArgb(130, 130, 130);
                    break;
                }
            }
        }
        private int PixelYToBeatY(int y)
        {
            return y / (channelHeight + channelPadding * 2);
        }
        private int BeatYToPixelY(int y)
        {
            return channelPadding + y * channelHeight + y * channelPadding * 2 + 1;
        }
        #endregion
    }
}
