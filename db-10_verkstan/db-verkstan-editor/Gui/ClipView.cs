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
    public partial class ClipView : UserControl
    {
        #region Properties
        private Clip clip;
        public Clip Clip
        {
            get
            {
                return clip;
            }
            set
            {
                clip = value;
                
                if (clip == null)
                {
                    generatorClipPropertiesView1.Visible = false;
                    generatorClipValueView1.Visible = false;
                    splineClipValueView1.Visible = false;
                    splineClipPropertiesView1.Visible = false;
                }       
                else if (clip.GetType() == typeof(GeneratorClip))
                {
                    splineClipPropertiesView1.Visible = false;
                    splineClipValueView1.Visible = false;
                    generatorClipPropertiesView1.GeneratorClip = (GeneratorClip)clip;
                    generatorClipValueView1.GeneratorClip = (GeneratorClip)clip;
                    generatorClipPropertiesView1.Visible = true;
                    generatorClipValueView1.Visible = true;
                    generatorClipValueView1.BeatWidth = Convert.ToInt32(numericUpDown1.Value);
                    generatorClipValueView1.YZoom = Convert.ToSingle(numericUpDown2.Value) / 200.0f;
                }
                else if (clip.GetType() == typeof(SplineClip))
                {
                    generatorClipPropertiesView1.Visible = false;
                    generatorClipValueView1.Visible = false;
                    splineClipPropertiesView1.SplineClip = (SplineClip)clip;
                    splineClipValueView1.SplineClip = (SplineClip)clip;
                    splineClipPropertiesView1.Visible = true;
                    splineClipValueView1.Visible = true;
                    splineClipValueView1.BeatWidth = Convert.ToInt32(numericUpDown1.Value);
                    splineClipValueView1.YZoom = Convert.ToSingle(numericUpDown2.Value) / 200.0f;
                }
            }
        }
        #endregion

        #region Constructor
        public ClipView()
        {
            InitializeComponent();
        }
        #endregion

        #region Event Handlers
        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            int beatWidth = Convert.ToInt32(numericUpDown1.Value);
            generatorClipValueView1.BeatWidth = beatWidth;
            splineClipValueView1.BeatWidth = beatWidth;
            clipValueHorizontalLine1.BeatWidth = beatWidth;
        }
        private void generatorClipValueView1_Resize(object sender, EventArgs e)
        {
            clipValueHorizontalLine1.Width = generatorClipValueView1.Width;                
            clipValueVerticalLine1.Height = generatorClipValueView1.Height;
            clipValueVerticalLine1.Refresh();
            UpdateScrollBars();
        }
        private void splineClipValueView1_Resize(object sender, EventArgs e)
        {
            clipValueHorizontalLine1.Width = splineClipValueView1.Width;
            clipValueVerticalLine1.Height = splineClipValueView1.Height;
            clipValueVerticalLine1.Refresh();
            UpdateScrollBars();
        }
        private void hScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            generatorClipValueView1.Left = -e.NewValue;
            splineClipValueView1.Left = -e.NewValue;
            clipValueHorizontalLine1.Left = -e.NewValue;
        }
        private void vScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            generatorClipValueView1.Top = -e.NewValue;
            splineClipValueView1.Top = -e.NewValue;
            clipValueVerticalLine1.Top = -e.NewValue;
        }
        private void numericUpDown2_ValueChanged(object sender, EventArgs e)
        {
            float yZoom = Convert.ToSingle(numericUpDown2.Value) / 100.0f;
            generatorClipValueView1.YZoom = yZoom;
            splineClipValueView1.YZoom = yZoom;
        }
        #endregion

        #region Private Methods
        private void UpdateScrollBars()
        {
            int w = 0;
            int h = 0;
            if (clip != null && clip.GetType() == typeof(GeneratorClip))
            {
                w = generatorClipValueView1.Width;
                h = generatorClipValueView1.Height;
            }
            else if (clip != null && clip.GetType() == typeof(SplineClip))
            {
                w = splineClipValueView1.Width;
                h = splineClipValueView1.Height;
            }

            hScrollBar1.Enabled = w > splitHorizontalLineAndValueView.Panel2.Width;
            vScrollBar1.Enabled = h > splitHorizontalLineAndValueView.Panel2.Height;

            hScrollBar1.Minimum = 0;
            hScrollBar1.Maximum = w;
            hScrollBar1.LargeChange = splitHorizontalLineAndValueView.Panel2.Width;
            hScrollBar1.SmallChange = 10;

            vScrollBar1.Minimum = 0;
            vScrollBar1.Maximum = h;
            vScrollBar1.LargeChange = splitHorizontalLineAndValueView.Panel2.Height;
            vScrollBar1.SmallChange = 10;

            if (!hScrollBar1.Enabled)
            {
                generatorClipValueView1.Left = 0;
                clipValueHorizontalLine1.Left = 0;
            }

            if (!vScrollBar1.Enabled)
            {
                generatorClipValueView1.Top = 0;
                clipValueVerticalLine1.Top = 0;
            }
        }
        #endregion
    }
}
