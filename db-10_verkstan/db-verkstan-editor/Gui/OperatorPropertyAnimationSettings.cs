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
    public partial class OperatorPropertyAnimationSettings : UserControl
    {
        public int Channel
        {
            set
            {
                channelNumericUpDown.Value = value;
            }
            get
            {
                return Convert.ToInt32(channelNumericUpDown.Value);
            }
        }
        public float Amplify
        {
            set
            {
                amplifyNumericUpDown.Value = Convert.ToDecimal(value);
            }
            get
            {
                return Convert.ToSingle(amplifyNumericUpDown.Value);
            }
        }

        public event EventHandler SettingsChanged;
        public void OnSettingsChanged()
        {
            if (SettingsChanged != null)
                SettingsChanged(this, new EventArgs());
        }

        public OperatorPropertyAnimationSettings()
        {
            InitializeComponent();
        }

        private void channelNumericUpDown_ValueChanged(object sender, EventArgs e)
        {
            Channel = Convert.ToInt32(channelNumericUpDown.Value);
            OnSettingsChanged();
        }

        private void amplifyNumericUpDown_ValueChanged(object sender, EventArgs e)
        {
            Amplify = Convert.ToSingle(amplifyNumericUpDown.Value);
            OnSettingsChanged();
        }
    }
}
