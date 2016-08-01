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
    public partial class SplineClipPropertiesView : UserControl
    {
        #region Properties
        private SplineClip splineClip;
        public SplineClip SplineClip
        {
            get
            {
                return splineClip;
            }
            set
            {
                splineClip = value;

                if (splineClip != null)
                {
                    comboBox1.SelectedIndex = splineClip.GetSplineType();
                }
            }
        }
        #endregion

        #region Constructors
        public SplineClipPropertiesView()
        {
            InitializeComponent();
        }
        #endregion

        #region Event Handlers
        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (splineClip != null)
                splineClip.SetSplineType(comboBox1.SelectedIndex);
        }
        #endregion
    }
}
