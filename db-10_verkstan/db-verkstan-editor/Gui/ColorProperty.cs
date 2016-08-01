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
    public partial class ColorProperty : UserControl
    {
        private Color color;
        public Color Color
        {
            set
            {
                color = value;
                ColorPropertyColor.BackColor = color;
                ColorPropertyR.Value = color.R;
                ColorPropertyG.Value = color.G;
                ColorPropertyB.Value = color.B;
            }
            get
            {
                return color;
            }
        }

        public ColorProperty()
        {
            InitializeComponent();
            ColorPropertyColor.BackColor = color;
        }

        public event EventHandler ColorChanged;

        public void OnColorChanged(Color color)
        {
            if (ColorChanged != null)
                ColorChanged(this, new EventArgs());
        }

        private void ColorPropertyR_ValueChanged(object sender, EventArgs e)
        {
            Color = Color.FromArgb((int)ColorPropertyR.Value, color.G, color.B);
            OnColorChanged(color);
        }

        private void ColorPropertyG_ValueChanged(object sender, EventArgs e)
        {
            Color = Color.FromArgb(color.R, (int)ColorPropertyG.Value, color.B);
            OnColorChanged(color);
        }

        private void ColorPropertyB_ValueChanged(object sender, EventArgs e)
        {
            Color = Color.FromArgb(color.R, color.G, (int)ColorPropertyB.Value);
            OnColorChanged(color);
        }
    }
}
