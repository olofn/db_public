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
    public partial class TimelinesView : UserControl
    {
        #region Properties
        public Clip ViewedClip
        {
            get
            {
                return timelineView1.ViewedClip;
            }
            set
            {
                timelineView1.ViewedClip = value;
            }
        }
        public Timeline Timeline
        {
            set
            {
                timelineView1.Timeline = value;
                viewedTimelineOperator = null;
            }
            get
            {
                return timelineView1.Timeline;
            }
        }
        private Operator viewedTimelineOperator;
        public Operator ViewedTimelineOperator
        {
            get
            {
                return viewedTimelineOperator;
            }
        }
        #endregion

        #region Constructors
        public TimelinesView()
        {
            InitializeComponent();
        }
        #endregion

        #region Event Handlers
        private void moveButton_Click(object sender, EventArgs e)
        {
            selectedToolLabel.Text = "Move Tool Selected";
            timelineView1.Mode = TimelineChannelsView.Modes.Move;
        }
        private void generatorButton_Click(object sender, EventArgs e)
        {
            selectedToolLabel.Text = "Generator Drawing Tool Selected";
            timelineView1.Mode = TimelineChannelsView.Modes.DrawGenerator;
        }
        private void splineButton_Click(object sender, EventArgs e)
        {
            selectedToolLabel.Text = "Spline Drawing Tool Selected";
            timelineView1.Mode = TimelineChannelsView.Modes.DrawSpline;
        }
        private void timelineView1_ViewedClipChanged(object sender, EventArgs e)
        {
            OnViewedClipChanged();
        }
        private void TimelinesView_VisibleChanged(object sender, EventArgs e)
        {
            if (Visible)
                Reset();
        }
        private void timelinesComboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            Operator op = Operator.FindWithUniqueName(timelinesComboBox1.SelectedItem.ToString());
            Timeline = op.Timeline;
            viewedTimelineOperator = op;
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

        #region Public Methods
        public void Reset()
        {
            timelinesComboBox1.Items.Clear();
            ICollection<Operator> operatorsWithTimeline = Operator.FindAllWithTimeline();

            foreach (Operator op in operatorsWithTimeline)
                timelinesComboBox1.Items.Add(op.UniqueName);

            if (viewedTimelineOperator != null)
                timelinesComboBox1.SelectedItem = viewedTimelineOperator.UniqueName;
        }
        #endregion
    }
}
