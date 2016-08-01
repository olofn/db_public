using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Design;
using VerkstanEditor.Logic;

namespace VerkstanEditor.Gui
{
    [ToolboxItem(true)]
    public partial class Transport : UserControl
    {
        #region Properties
        private Project project;
        public Project Project
        {
            get
            {
                return project;
            }
            set
            {
                project = value;
                if (project != null)
                {
                    bpm.Value = project.BPM;
                    Metronome.BPM = project.BPM;
                }
            }
        }
        #endregion

        #region Private Variables
        private bool showClockAsBeats = true;
        private int tick;
        #endregion

        #region Constructor
        public Transport()
        {
            InitializeComponent();
            this.bpm.Value = Metronome.BPM;
            this.beatsOrTime.Text = "Beats";
            UpdateClock();
            Metronome.BeatChangedFastUpdate += new Metronome.BeatChangedHandler(this.Transport_BeatChangedFastUpdate);
        }
        #endregion

        #region Event Handlers
        public void Transport_BeatChangedFastUpdate(int tick)
        {
            this.tick = tick;
            UpdateClock();
        }
        private void play_Click(object sender, EventArgs e)
        {
            //Metronome.Loop = false;
            Metronome.Start();
        }
        private void stop_Click(object sender, EventArgs e)
        {
            Metronome.Pause();
            Metronome.Tick = 0;
        }
        private void start_Click(object sender, EventArgs e)
        {
            Metronome.Tick = 0;
        }
        private void pause_Click(object sender, EventArgs e)
        {
            Metronome.Pause();
        }
        private void bpm_ValueChanged(object sender, EventArgs e)
        {
            Metronome.BPM = Convert.ToInt32(this.bpm.Value);
            if (project != null)
                project.BPM = Metronome.BPM;
        }
        private void beatsOrTime_SelectedValueChanged(object sender, EventArgs e)
        {
            showClockAsBeats = (String)beatsOrTime.SelectedItem == "Beats";
            UpdateClock();

            int clockX = Size.Width / 2 - this.time.Size.Width / 2;
            this.time.Location = new Point(clockX, this.time.Location.Y);  
        }
        private void Transport_Resize(object sender, EventArgs e)
        {
            int clockX = Size.Width / 2 - this.time.Size.Width / 2;
            this.time.Location = new Point(clockX, this.time.Location.Y);

            int bpmX = Size.Width - this.bpm.Width - 3;
            this.bpm.Location = new Point(bpmX, this.bpm.Location.Y);

            int bpmLabelX = Size.Width - this.bpm.Width - this.label1.Size.Width - 3;
            this.label1.Location = new Point(bpmLabelX, this.label1.Location.Y);

            int beatsOrTimeLabelX = Size.Width - this.beatsOrTime.Width - this.label2.Size.Width - 3;
            this.label2.Location = new Point(beatsOrTimeLabelX, this.label2.Location.Y);

            int beatsOrTimeX = Size.Width - this.beatsOrTime.Width - 3;
            this.beatsOrTime.Location = new Point(beatsOrTimeX, this.beatsOrTime.Location.Y);

            this.miniTimeline1.Size = new Size(Size.Width - 8, miniTimeline1.Size.Height);
        }
        private void loopPlay_Click(object sender, EventArgs e)
        {
           //Metronome.Loop = true;
           // Metronome.Start();
        }
        #endregion

        #region Private Methods
        private void UpdateClock()
        {
          
            if (showClockAsBeats)
            {
                float bf = this.tick / (float)Metronome.TicksPerBeat;
                this.time.Text = String.Format("{0:0000.00}", bf + 1);
            }
            else
            {
                TimeSpan ts = TimeSpan.FromMilliseconds(Metronome.Milliseconds);
                this.time.Text = String.Format("{0:00}:{1:00}:{2:00}", (int)ts.TotalMinutes, ts.Seconds, (int)(ts.Milliseconds / 10.0f));
            }
        }
        #endregion
    }
}
