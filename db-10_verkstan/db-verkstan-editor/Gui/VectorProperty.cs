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
    [ToolboxItem(true)]
    public partial class VectorProperty : UserControl
    {
        public float X
        {
            set
            {
                x.Value = Convert.ToDecimal(value);
            }
            get
            {
                return Convert.ToSingle(x.Value);
            }
        }
        public float Y
        {
            set
            {
                y.Value = Convert.ToDecimal(value);
            }
            get
            {
                return Convert.ToSingle(y.Value);
            }
        }
        public float Z
        {
            set
            {
                z.Value = Convert.ToDecimal(value);
            }
            get
            {
                return Convert.ToSingle(z.Value);
            }
        }

        public VectorProperty()
        {
            InitializeComponent();
        }

        public event EventHandler ValueChanged;

        public void OnValueChanged()
        {
            if (ValueChanged != null)
                ValueChanged(this, new EventArgs());
        }

        private void z_ValueChanged(object sender, EventArgs e)
        {
            OnValueChanged();
        }

        private void y_ValueChanged(object sender, EventArgs e)
        {
            OnValueChanged();
        }

        private void x_ValueChanged(object sender, EventArgs e)
        {
            OnValueChanged();
        }
    }
}
