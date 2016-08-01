using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using Midi;

namespace VorlonSeq
{
    public partial class ChannelEditor : UserControl
    {
        public ChannelEditor()
        {
            InitializeComponent();
            channelTimeline1.ClipEditRequested += new ChannelTimeline.ClipEditRequest(channelTimeline1_ClipEditRequested);
        }

        void channelTimeline1_ClipEditRequested(VorlonSeq.Seq.Clip clip)
        {
            OnClipEditRequested(clip);
        }

        public delegate void ClipEditRequest(VorlonSeq.Seq.Clip clip);
        public event ClipEditRequest ClipEditRequested;

        private void OnClipEditRequested(VorlonSeq.Seq.Clip clicked)
        {
            if (ClipEditRequested != null)
            {
                ClipEditRequested(clicked);
            }
        }

        public void OnMidiInput(MidiMessage message)
        {
            channelTimeline1.OnMidiInput(message);
        }
    }
}
