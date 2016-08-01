using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using DB.Darkfile;

using Vorlon2;

using Midi;

namespace VorlonSeq.Seq
{
    public class Clip : IChunkReader
    {
        public class Event
        {
            public Event(DarkInStream s)
            {
                s.Read(out Time);
                Message = new MidiMessage(s.ReadUInt());
            }

            public Event(MidiMessage message, int time)
            {
                Message = message;
                Time = time;
            }

            public Event Clone()
            {
                return new Event(Message, Time);
            }

            public MidiMessage Message;
            public int Time;
        }

        public class NoteEvent
        {
            public byte Note;
            public byte Velocity;
            public int StartTime;
            public int Length;

            public NoteEvent(DarkInStream s)
            {
                s.Read(out StartTime);
                s.Read(out Note);
                s.Read(out Velocity);
                s.Read(out Length);
            }

            public NoteEvent(byte note, byte velocity, int startTime, int length)
            {
                StartTime = startTime;
                Note = note;
                Velocity = velocity;                
                Length = length;
            }

            public int EndTime { get { return StartTime + Length; } set { Length = value - StartTime; } }

            public Event ToEvent(MidiMessage.Commands command)
            {
                if (command == MidiMessage.Commands.NoteOn)
                {
                    return new Event(new MidiMessage(0, MidiMessage.Commands.NoteOn, (uint)Note, (uint)Velocity), StartTime);
                }
                else if (command == MidiMessage.Commands.NoteOff)
                {
                    return new Event(new MidiMessage(0, MidiMessage.Commands.NoteOff, (uint)Note, 0), StartTime + Length); 
                }

                throw new Exception("Command must be NoteOn or NoteOff");
            }

            public NoteEvent Clone()
            {
                return new NoteEvent(Note, Velocity, StartTime, Length);
            }
        }

        public Channel Channel;
        public readonly List<Event> ControllerEvents = new List<Event>();
        public readonly List<NoteEvent> NoteEvents = new List<NoteEvent>();
        public int StartTime = 0;
        public int Length = 64;
        public int EndTime { get { return StartTime + Length; } set { Length = value - StartTime; } }

        public List<MidiMessage> GetAllEventsBetween(int start, int end)
        {
            List<MidiMessage> result = new List<MidiMessage>();
            
            foreach (Event e in ControllerEvents)
            {
                if (e.Time >= start && e.Time < end)
                {
                    result.Add(e.Message);
                }
            }

            foreach (NoteEvent e in NoteEvents)
            {
                if (e.EndTime >= start && e.EndTime < end)
                {
                    result.Add(e.ToEvent(MidiMessage.Commands.NoteOff).Message);
                }
            }

            foreach (NoteEvent e in NoteEvents)
            {
                if (e.StartTime >= start && e.StartTime < end)
                {
                    result.Add(e.ToEvent(MidiMessage.Commands.NoteOn).Message);
                }
            }

            return result;
        }

        public Clip Clone()
        {
            Clip c = new Clip();
            c.Channel = Channel;
            c.StartTime = StartTime;
            c.Length = Length;
            foreach (Event e in ControllerEvents)
            {
                c.ControllerEvents.Add(e.Clone());
            }

            foreach (NoteEvent e in NoteEvents)
            {
                c.NoteEvents.Add(e.Clone());
            }
            return c;
        }

        public void Write(DarkOutStream s)
        {
            s.Write(StartTime);
            s.Write(Length);

            s.OpenChunk("NOTE");
            s.Write(NoteEvents.Count);            
            foreach (NoteEvent e in NoteEvents)
            {
                s.Write(e.StartTime);
                s.Write(e.Note);
                s.Write(e.Velocity);
                s.Write(e.Length);
            }
            s.CloseChunk();

            s.OpenChunk("CTRL");
            s.Write(ControllerEvents.Count);
            foreach (Event e in ControllerEvents)
            {
                s.Write(e.Time);
                s.Write(e.Message.GetAsUInt());
            }
            s.CloseChunk();
        }

        public void Read(DarkInStream s)
        {
            s.Read(out StartTime);
            s.Read(out Length);
            s.ReadAllChunks(this);
        }

        public void ReadChunk(string id, long length, DarkInStream s)
        {
            if (id.Equals("NOTE"))
            {
                int numNoteEvents = s.ReadInt();
                for (int i = 0; i < numNoteEvents; i++)
                {
                    NoteEvents.Add(new NoteEvent(s));
                }
            }

            if (id.Equals("CTRL"))
            {
                int numControllerEvents = s.ReadInt();
                for (int i = 0; i < numControllerEvents; i++)
                {
                    ControllerEvents.Add(new Event(s));
                }
            }
        }
    }

    public class Patch
    {
        public const int NumControllers = 127;
        private byte[] controllers = new byte[NumControllers];
        private const byte notSet = 255;
        public Channel Channel = null;
        public int Time = 0;

        public Patch()
        {
            for (int i = 0; i < controllers.Length; i++)
            {
                controllers[i] = notSet;
            }
        }

        public Patch(DarkInStream s) : this()
        {
            s.Read(out Time);
            s.ReadByteArray(controllers);
        }

        public void Set(MidiMessage m)
        {
            if (m.Command == MidiMessage.Commands.Controller)
            {
                controllers[m.Param1] = (byte)m.Param2;
            }
        }

        public IList<MidiMessage> Get()
        {
            List<MidiMessage> res = new List<MidiMessage>();
            for (int i = 0; i < controllers.Length; i++)
            {
                if (controllers[i] == notSet)
                {
                    continue;
                }

                res.Add(new MidiMessage((uint)Channel.Number, MidiMessage.Commands.Controller, (uint)i, controllers[i]));
            }
            return res;
        }

        public void Write(DarkOutStream s)
        {
            s.Write(Time);
            s.WriteByteArray(controllers);
        }
    }

    public class Channel : IChunkReader
    {
        public readonly int Number;
        public string Name;
        public readonly List<Clip> clips = new List<Clip>();
        public readonly List<Patch> patches = new List<Patch>();

        public IList<Clip> Clips { get { return clips.AsReadOnly(); } }
        public IList<Patch> Patches { get { return patches.AsReadOnly(); } }

        public void AddClip(Clip c)
        {
            clips.Add(c);
            c.Channel = this;
        }

        public void RemoveClip(Clip c)
        {
            if (clips.Remove(c))
            {
                c.Channel = null;
            }
        }

        public void AddPatch(Patch p)
        {
            patches.Add(p);
            p.Channel = this;
        }

        public void RemovePatch(Patch p)
        {
            if (patches.Remove(p))
            {
                p.Channel = null;
            }
        }

        public Channel(int number)
        {
            Number = number;
            Name = "Channel #" + number;
        }

        public List<MidiMessage> GetAllEventsBetween(int start, int end)
        {
            List<MidiMessage> result = new List<MidiMessage>();
            foreach (Clip c in Clips)
            {
                if (end <= c.StartTime || start > c.EndTime)
                {
                    continue;
                }

                result.AddRange(c.GetAllEventsBetween(start - c.StartTime, end - c.StartTime));
            }

            foreach (Patch p in Patches)
            {
                if (end <= p.Time || start > p.Time)
                {
                    continue;
                }

                result.AddRange(p.Get());
            }

            for (int i = 0; i < result.Count; i++)
            {
                MidiMessage m = result[i];
                m.Channel = (uint)Number;
                result[i] = m;
            }

            return result;
        }

        public Clip GetClipAt(int time)
        {
            foreach (Clip c in Clips)
            {
                if (c.StartTime <= time && c.EndTime > time)
                {
                    return c;
                }
            }

            return null;
        }

        public void Write(DarkOutStream s)
        {
            foreach (Clip c in Clips)
            {
                s.OpenChunk("CLIP");
                c.Write(s);
                s.CloseChunk();
            }

            foreach (Patch p in Patches)
            {
                s.OpenChunk("PTCH");
                p.Write(s);
                s.CloseChunk();
            }
        }

        public void ReadChunk(string id, long length, DarkInStream s)
        {
            if (id.Equals("CLIP"))
            {
                Clip c = new Clip();
                c.Read(s);
                AddClip(c);
            }
            else if (id.Equals("PTCH"))
            {
                Patch p = new Patch(s);
                AddPatch(p);
            }
        }
    }

    public class Song : IChunkReader
    {
        public const int NumChannels = 16;

        public Channel[] Channels = new Channel[NumChannels];

        public readonly int TicksPerBeat = 4;
        public readonly int BeatsPerBar = 4;
        public int TicksPerBar { get { return TicksPerBeat * BeatsPerBar; } }

        public Song()
        {
            for (int i = 0; i < Channels.Length; i++)
            {
                Channels[i] = new Channel(i);
                Channels[i].AddPatch(new Patch());
            }
        }

        public void Write(DarkOutStream s)
        {            
            for (int i = 0; i < Channels.Length; i++)
            {
                s.OpenChunk("CHAN");
                s.Write(i);
                Channels[i].Write(s);
                s.CloseChunk();
            }                
        }

        public void ReadChunk(string id, long length, DarkInStream s)
        {
            if (id.Equals("CHAN"))
            {
                int index;
                s.Read(out index);
                Channels[index] = new Channel(index);
                s.ReadAllChunks(Channels[index]);
            }
        }
    }

    public class Sequencer
    {
        public static Song Song = new Song();
        static public int FramesPerTick = 21;
        public static VorlonSynth Synth = new VorlonSynth();

        private static List<MidiMessage> toBePlayed = new List<MidiMessage>();
        private static bool running = false;

        public static bool IsPlaying = false;
        static int playPosition = 0;
        private static int frameCounter = 0;

        public delegate void PlayCursorMovedHandler(int pos);
        public static event PlayCursorMovedHandler PlayCursorMoved;

        public static int PlayPosition
        {
            get { return playPosition; }
            set
            {
                if (playPosition != value)
                {
                    playPosition = value;
                    if (PlayCursorMoved != null)
                    {
                        PlayCursorMoved(playPosition);
                    }
                }
            }
        }

        public static int BPM 
        { 
            get 
            {
                double samplesPerBeat = FramesPerTick * Synth.FrameSize * 4;
                double beatsPerSecond = Synth.SampleRate / samplesPerBeat;
                return (int)(beatsPerSecond * 60.0f);                
            }
        }

        public static void Load(string path)
        {
            DarkInStream dis = new DarkInStream(File.OpenRead(path));
            Song = new Song();            
            dis.ReadChunk(delegate(string id, long length, DarkInStream s)
            {
                if (id.Equals("VSEQ"))
                {
                    s.Read(out FramesPerTick);

                    s.ReadChunk(delegate(string id2, long length2, DarkInStream s2)
                    {
                        if (id2.Equals("SONG"))
                        {
                            s2.ReadAllChunks(Song);
                        }
                    });
                }
            });
            dis.Close();

            foreach (Channel c in Song.Channels)
            {
                foreach (MidiMessage m in c.Patches[0].Get())
                {
                    PlayMidiEvent(m, false);
                }
            }
        }

        public static void Reset()
        {
            FramesPerTick = 21;
            Song = new Song();
        }

        public static void Save(string path)
        {
            DarkOutStream dos = new DarkOutStream(File.Create(path));
            dos.OpenChunk("VSEQ");
            dos.Write(FramesPerTick);
            dos.OpenChunk("SONG");
            Song.Write(dos);
            dos.CloseChunk();
            dos.CloseChunk();
            dos.Close();
        }

        public static void PlayMidiEvent(MidiMessage midiMessage, bool fromKeyboard)
        {
            if (fromKeyboard)
            {
                // TODO: Fix this hax
                Channel c = Song.Channels[midiMessage.Channel];
                Patch p = c.Patches[0];
                p.Set(midiMessage);
            }

            lock (toBePlayed)
            {
                toBePlayed.Add(midiMessage);
            }
        }

        private static void SendPendingMidiToVorlon()
        {
            lock (toBePlayed)
            {
                foreach (MidiMessage m in toBePlayed)
                {
                    Synth.MidiInput(m.GetAsUInt());
                }
                toBePlayed.Clear();
            }
        }

        public static void StartVorlon()
        {
            if (running)
            {
                return;
            }

            running = true;
            new System.Threading.Thread(VorlonLoop).Start();
        }

        public static void StopVorlon()
        {
            running = false;
        }

        private static void StepSequencer()
        {
            if (!IsPlaying)
            {
                return;
            }

            frameCounter++;

            if (frameCounter >= FramesPerTick)
            {
                frameCounter = 0;
                for (int i = 0; i < Song.NumChannels; i++)
                {
                    Channel channel = Song.Channels[i];
                    IList<MidiMessage> events = channel.GetAllEventsBetween(PlayPosition, PlayPosition + 1);
                    foreach (MidiMessage m in events)
                    {
                        PlayMidiEvent(m, false);
                    }
                }
                PlayPosition++;
            }
        }

        private static void VorlonLoop()
        {
            while (running)
            {
                StepSequencer();
                SendPendingMidiToVorlon();
                Synth.PlayFrame();
            }
        }
    }
}
