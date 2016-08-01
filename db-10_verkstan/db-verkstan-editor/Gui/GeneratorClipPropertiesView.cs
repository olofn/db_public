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
    public partial class GeneratorClipPropertiesView : UserControl
    {
        #region Properties
        private GeneratorClip generatorClip;
        public GeneratorClip GeneratorClip
        {
            get
            {
                return generatorClip;
            }
            set
            {
                generatorClip = value;
             
                if (generatorClip != null)
                {
                    comboBox1.SelectedIndex = generatorClip.GetGeneratorType();
                    numericUpDown1.Value = Convert.ToDecimal(generatorClip.GetPeriodInTicks() / (float)Metronome.TicksPerBeat);
                }
            }
        }
        #endregion

        #region Constructor
        public GeneratorClipPropertiesView()
        {
            InitializeComponent();
            comboBox1.SelectedIndex = 0;
        }
        #endregion

        #region Event Handlers
        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (generatorClip != null)
                generatorClip.SetGeneratorType(comboBox1.SelectedIndex);
        }
        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            if (generatorClip != null)
                generatorClip.SetPeriodInTicks((int)(Convert.ToSingle(numericUpDown1.Value) * Metronome.TicksPerBeat));
        }
        #endregion
    }
}
