using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace VorlonSeq
{
    public partial class ClipEditor : UserControl
    {
        public Seq.Clip Clip { set { pianoRoll1.Clip = value; } }

        public ClipEditor()
        {
            InitializeComponent();
        }

        public void OnMidiInput(Midi.MidiMessage message)
        {
            pianoRoll1.OnMidiInput(message);
        }
    }
}
