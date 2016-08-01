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
    public partial class TimelineChannelPropertiesView : UserControl
    {
        #region Properties
        public int Value
        {
            get
            {
                return Convert.ToInt32(numericUpDown1.Value);
            }
            set
            {
                numericUpDown1.Value = value;
            }
        }
        #endregion

        #region Constructors
        public TimelineChannelPropertiesView()
        {
            InitializeComponent();
        }
        #endregion

        #region Event Handlers
        private void numericUpDown1_MouseDown(object sender, MouseEventArgs e)
        {
            OnMouseDown(new MouseEventArgs(e.Button, e.Clicks, e.X, e.Y + numericUpDown1.Top, e.Delta));
        }
        private void TimelineChannelPropertiesView_Resize(object sender, EventArgs e)
        {
            label1.Top = Height / 2 - label1.Height / 2;
            numericUpDown1.Top = Height / 2 - numericUpDown1.Height / 2;
        }
        private void label1_MouseDown(object sender, MouseEventArgs e)
        {
            OnMouseDown(new MouseEventArgs(e.Button, e.Clicks, e.X, e.Y + label1.Top, e.Delta));
        }
        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            OnValueChanged();
        }
        #endregion      

        #region Events
        public event EventHandler ValueChanged;
        protected void OnValueChanged()
        {
            if (ValueChanged != null)
                ValueChanged(this, new EventArgs());
        }
        #endregion 
    }
}
