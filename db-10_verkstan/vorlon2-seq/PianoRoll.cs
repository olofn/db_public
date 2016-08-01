using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using VorlonSeq.Seq;
using Midi;

namespace VorlonSeq
{
    public partial class PianoRoll : UserControl
    {        
        const int numKeys = 127;
        int keyHeight = 7;
        int pixelsPerTick = 10;
        public Clip Clip;
        byte tryingKey = 128;
        private Clip.NoteEvent paintedNote = null;
        private bool moving = false;
        private bool copying = false;
        private bool shift = false;
        private bool selecting = false;
        private List<Clip.NoteEvent> selected = new List<Clip.NoteEvent>();
        static Point mouseDownPos;
        static Point mousePos;

        public PianoRoll()
        {
            InitializeComponent();

            this.SetStyle(
                ControlStyles.AllPaintingInWmPaint |
                ControlStyles.UserPaint |
                ControlStyles.DoubleBuffer, true);
            
            Refresh();

            // TEMP TEST
            Clip = new Clip();
            Clip.NoteEvents.Add(new Clip.NoteEvent(50, 100, 4, 8));
            Clip.NoteEvents.Add(new Clip.NoteEvent(52, 100, 10, 8));
        }

        private void PianoRoll_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;

            for (int i = 0; i < numKeys; i++)
            {
                int key = numKeys - i - 1;
                int y = i * keyHeight;
                bool blackKey = (key % 12 == 1 || key % 12 == 3 || key % 12 == 6 || key % 12 == 8 || key % 12 == 10);
                g.FillRectangle(blackKey ? Brushes.Silver : Brushes.LightGray, new Rectangle(0, y, Width, keyHeight - 1));
            }

            for (int x = 0; x < Width; x += pixelsPerTick)
            {
                g.DrawLine(Pens.White, new Point(x, 0), new Point(x, Height));
                
                if ((x / pixelsPerTick) % 4 == 0)
                {
                    g.DrawLine(Pens.White, new Point(x - 1, 0), new Point(x - 1, Height));
                }

                if ((x / pixelsPerTick) % 16 == 0)
                {
                    g.DrawLine(Pens.White, new Point(x + 1, 0), new Point(x + 1, Height));
                }
            }

            if (Clip != null)
            {                
                foreach(Clip.NoteEvent note in Clip.NoteEvents)
                {
                    Rectangle r = NoteToRect(note);
                    g.FillRectangle(Brushes.RosyBrown, r);
                    g.DrawRectangle(Pens.Black, r);
                    if (selected.Contains(note))
                    {
                        r.Inflate(new Size(-1, -1));
                        g.DrawRectangle(Pens.Black, r);
                    }
                }

                if (moving)
                {
                    int timeDelta = GetTimeMovement();
                    int keyDelta = GetKeyMovement();
                    foreach (Clip.NoteEvent n in selected)
                    {
                        Clip.NoteEvent moved = new Clip.NoteEvent((byte)(n.Note + keyDelta), n.Velocity, n.StartTime + timeDelta, n.Length);
                        Rectangle r = NoteToRect(moved);
                        r.Inflate(new Size(-1, -1));
                        g.DrawRectangle(Pens.Black, r);
                    }
                }
            }

            if (paintedNote != null)
            {
                Rectangle r = NoteToRect(paintedNote);
                g.DrawRectangle(Pens.Black, r);
            }

            if (selecting)
            {
                g.DrawRectangle(Pens.DarkGray, GetSelectRect());
            }
        }

        Rectangle NoteToRect(Clip.NoteEvent note)
        {
            int i = numKeys - note.Note - 1;
            int y = i * keyHeight - 1;
            int h = keyHeight;
            int x = note.StartTime * pixelsPerTick;
            int w = note.Length * pixelsPerTick - 1;
            return new Rectangle(x, y, w, h);
        }

        byte ConvertYToKey(int y)
        {
            return (byte)Math.Min(Math.Max((Height - y - 1) / keyHeight, 0), 127);
        }

        int ConvertXToTime(int x)
        {
            return x / pixelsPerTick;
        }

        int GetTimeMovement()
        {
            int delta = (mousePos.X - mouseDownPos.X) / pixelsPerTick;
            foreach(Clip.NoteEvent n in selected)
            {
                if (n.StartTime + delta < 0)
                {
                    delta = -n.StartTime;
                }
            }
            return delta;
        }

        int GetKeyMovement()
        {
            int delta = (int)ConvertYToKey(mousePos.Y) - (int)ConvertYToKey(mouseDownPos.Y);
            foreach (Clip.NoteEvent n in selected)
            {
                if (n.Note + delta < 0)
                {
                    delta = -n.Note;
                }

                if (n.Note + delta > 127)
                {
                    delta = 127 - n.Note;
                }
            }
            return delta;
        }

        Clip.NoteEvent GetNoteAt(Point loc)
        {
            foreach (Clip.NoteEvent n in Clip.NoteEvents)
            {
                if (NoteToRect(n).Contains(loc))
                {
                    return n;
                }
            }
            return null;
        }

        private void PianoRoll_Layout(object sender, LayoutEventArgs e)
        {
            Size = new Size(Width, numKeys * keyHeight);
        }

        private void UpdatePaintedNote(int x)
        {
            if (paintedNote != null)
            {
                paintedNote.EndTime = ConvertXToTime(x);
                paintedNote.Length = Math.Max(paintedNote.Length, 1);
            }
        }

        private void PianoRoll_MouseDown(object sender, MouseEventArgs e)
        {
            mousePos = e.Location;
            mouseDownPos = e.Location;

            if (e.Button == MouseButtons.Right)
            {
                tryingKey = ConvertYToKey(e.Y);
                uint channel = (uint)Clip.Channel.Number;
                Sequencer.PlayMidiEvent(new Midi.MidiMessage(channel, Midi.MidiMessage.Commands.NoteOn, tryingKey, 110), false);
            }

            if (e.Button == MouseButtons.Left)
            {
                selecting = shift;
            }

            if (e.Button == MouseButtons.Left && !selecting)
            {
                Clip.NoteEvent clickedNote = GetNoteAt(e.Location);
                if (clickedNote == null)
                {
                    byte key = ConvertYToKey(e.Y);
                    int time = ConvertXToTime(e.X);
                    paintedNote = new Clip.NoteEvent(key, 110, time, 1);
                    Refresh();
                }
                else
                {
                    if (!selected.Contains(clickedNote))
                    {
                        selected.Clear();
                        selected.Add(clickedNote);
                    }
                    moving = true;
                    Refresh();
                }
            }

            if (e.Button == MouseButtons.Left && selecting)
            {
                selected.Clear();
                Refresh();
            }
        }

        private void PianoRoll_MouseUp(object sender, MouseEventArgs e)
        {
            mousePos = e.Location;

            if (e.Button == MouseButtons.Right)
            {
                uint channel = (uint)Clip.Channel.Number;
                Sequencer.PlayMidiEvent(new Midi.MidiMessage(channel, Midi.MidiMessage.Commands.NoteOff, tryingKey, 0), true);
                tryingKey = 128;
            }            

            if (e.Button == MouseButtons.Left && paintedNote != null)
            {
                UpdatePaintedNote(e.X);
                Clip.NoteEvents.Add(paintedNote);
                selected.Clear();
                selected.Add(paintedNote);
                paintedNote = null;
                Refresh();
            }

            if (e.Button == MouseButtons.Left && moving)
            {
                int timeDelta = GetTimeMovement();
                int keyDelta = GetKeyMovement();
                List<Clip.NoteEvent> moved = new List<Clip.NoteEvent>();
                foreach (Clip.NoteEvent ne in selected)
                {
                    Clip.NoteEvent n = ne;
                    if (copying)
                    {
                        n = n.Clone();
                        Clip.NoteEvents.Add(n);
                    }
                    n.StartTime += timeDelta;
                    n.Note = (byte)(n.Note + keyDelta);
                    moved.Add(n);
                }
                selected.Clear();
                selected.AddRange(moved);
                moving = false;
                Refresh();
            }

            if (e.Button == MouseButtons.Left && selecting)
            {
                Rectangle selectRect = GetSelectRect();
                foreach (Clip.NoteEvent n in Clip.NoteEvents)
                {
                    if (NoteToRect(n).IntersectsWith(selectRect))
                    {
                        selected.Add(n);
                    }
                }
                selecting = false;
                Refresh();
            }
        }

        private void PianoRoll_MouseMove(object sender, MouseEventArgs e)
        {
            mousePos = e.Location;

            if (e.Button == MouseButtons.Left && paintedNote != null)
            {
                int l = paintedNote.Length;
                UpdatePaintedNote(e.X);
                if (l != paintedNote.Length)
                {
                    Refresh();
                }
            }

            if (e.Button == MouseButtons.Left && (moving || selecting))
            {
                Refresh();
            }
        }

        private Rectangle GetSelectRect()
        {
            int x1 = Math.Min(mousePos.X, mouseDownPos.X);
            int y1 = Math.Min(mousePos.Y, mouseDownPos.Y);
            int x2 = Math.Max(mousePos.X, mouseDownPos.X);
            int y2 = Math.Max(mousePos.Y, mouseDownPos.Y);
            return new Rectangle(x1, y1, x2 - x1, y2 - y1);
        }

        private void PianoRoll_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Delete)
            {
                foreach(Clip.NoteEvent n in selected)
                {
                    Clip.NoteEvents.Remove(n);
                }
                selected.Clear();
                Refresh();
            }

            if (e.KeyCode == Keys.ControlKey)
            {
                copying = true;
            }

            if (e.KeyCode == Keys.ShiftKey)
            {
                shift = true;
            }
        }

        public void OnMidiInput(MidiMessage message)
        {
            message.Channel = (uint)Clip.Channel.Number;
            Sequencer.PlayMidiEvent(message, true);
        }

        private void PianoRoll_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.ControlKey)
            {
                copying = false;
            }

            if (e.KeyCode == Keys.ShiftKey)
            {
                shift = false;
            }
        }
    }
}
