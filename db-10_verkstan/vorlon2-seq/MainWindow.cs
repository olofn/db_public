using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using Midi;

namespace VorlonSeq
{
    public partial class mainWindow : Form
    {
        MidiInDevice.MidiInHandler handlerKeepalive;
        MidiInDevice midiDevice = null;
        int selectedTab = 0;
        string filename = null;
        bool needsRefresh = false;
        bool enableUF6Hack = false;

        public mainWindow()
        {
            handlerKeepalive = new MidiInDevice.MidiInHandler(OnMidiInput);
            InitializeComponent();
            framesPerTickUpDown.Value = Seq.Sequencer.FramesPerTick;
            channelEditor1.ClipEditRequested += new ChannelEditor.ClipEditRequest(channelEditor1_ClipEditRequested);

            int i = 0;
            MidiInDevice firstDevice = null;
            foreach(MidiInDevice device in MidiInDevice.EnumerateDevices()) {
                if (firstDevice == null)
                {
                    firstDevice = device;
                }
                ToolStripMenuItem item = new ToolStripMenuItem(device.Name);
                item.Tag = device;
                item.DropDownItemClicked += midiToolStripMenuItem_DropDownItemClicked;
                midiToolStripMenuItem.DropDownItems.Insert(i++, item);
            }

            if (firstDevice != null)
            {
                SwitchToMidiDevice(firstDevice);
            }

            Seq.Sequencer.PlayCursorMoved += new VorlonSeq.Seq.Sequencer.PlayCursorMovedHandler(Sequencer_PlayCursorMoved);
        }

        delegate void VoidDelegate();

        void Sequencer_PlayCursorMoved(int pos)
        {
            needsRefresh = true;
        }
  
        void channelEditor1_ClipEditRequested(VorlonSeq.Seq.Clip clip)
        {
            clipEditor1.Clip = clip;
            tabControl1.SelectTab(1);
        }

        private void framesPerTickUpDown_ValueChanged(object sender, EventArgs e)
        {
            Seq.Sequencer.FramesPerTick = (int)framesPerTickUpDown.Value;
            bpmLabel.Text = "= " + Seq.Sequencer.BPM + " BPM";
        }

        private void mainWindow_FormClosed(object sender, FormClosedEventArgs e)
        {
            SwitchToMidiDevice(null);
            Seq.Sequencer.StopVorlon();
        }

        private void playButton_Click(object sender, EventArgs e)
        {
            Seq.Sequencer.IsPlaying = !Seq.Sequencer.IsPlaying;
        }

        private void rewindButton_Click(object sender, EventArgs e)
        {
            Seq.Sequencer.PlayPosition = 0;
        }

        private void midiToolStripMenuItem_DropDownItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            SwitchToMidiDevice((MidiInDevice)e.ClickedItem.Tag);
        }

        private void SwitchToMidiDevice(MidiInDevice device)
        {
            foreach (ToolStripItem item in midiToolStripMenuItem.DropDownItems)
            {
                if (item is ToolStripMenuItem)
                {
                    ((ToolStripMenuItem)item).Checked = (item.Tag == device);
                }
            }

            if (midiDevice != null)
            {
                midiDevice.Stop();
                midiDevice.Close();
            }

            midiDevice = device;

            if (midiDevice != null)
            {
                enableUF6Hack = midiDevice.Name.Equals("UF MIDI IN");

                midiDevice.Open(handlerKeepalive);
                midiDevice.Start();
            }
        }

        void OnMidiInput(MidiInDevice sender, MidiMessage message)
        {
            if (enableUF6Hack)
            {
                if (message.Command == MidiMessage.Commands.Controller && message.Param1 == 7)
                {
                    message.Param1 = message.Channel + 11;
                }
            }

            if (selectedTab == 0)
            {
                channelEditor1.OnMidiInput(message);                
            }
            else
            {
                clipEditor1.OnMidiInput(message);
            }
        }

        private void tabControl1_SelectedIndexChanged(object sender, EventArgs e)
        {
            selectedTab = tabControl1.SelectedIndex;
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (filename == null)
            {
                saveAsToolStripMenuItem_Click(null, null);
            }
            else
            {
                Seq.Sequencer.Save(filename);
            }
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DialogResult res = openFileDialog1.ShowDialog();
            if (res == DialogResult.OK)
            {
                filename = openFileDialog1.FileName;
                Seq.Sequencer.Load(filename);
                framesPerTickUpDown.Value = Seq.Sequencer.FramesPerTick;
            }
            Refresh();
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                DialogResult res = saveFileDialog1.ShowDialog();
                if (res == DialogResult.OK)
                {
                    filename = saveFileDialog1.FileName;
                    Seq.Sequencer.Save(filename);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Save error");
            }
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Seq.Sequencer.Reset();
            filename = null;
            framesPerTickUpDown.Value = Seq.Sequencer.FramesPerTick;
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void refreshTimer_Tick(object sender, EventArgs e)
        {
            if (needsRefresh)
            {
                needsRefresh = false;
                tabControl1.Refresh();
            }
        }
    }
}
