using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Midi
{
    public class MidiInDevice : IDisposable
    {
        public readonly int Id;
        WinMM.MidiInCaps caps;
        private int handle = -1;
        private bool opened = false;
        private bool started = false;
        WinMM.MidiInProc proc; // Member, since it must not be GCed

        public string Name { get { return caps.Name; } }

        private MidiInDevice(int id, WinMM.MidiInCaps caps)        
        {
            Id = id;
            this.caps = caps;
        }       

        public static IList<MidiInDevice> EnumerateDevices()
        {
            List<MidiInDevice> devices = new List<MidiInDevice>();

            uint numInputDevices = WinMM.midiInGetNumDevs();

            for (int i = 0; i < numInputDevices; i++)
            {
                WinMM.MidiInCaps inCaps = new WinMM.MidiInCaps();
                WinMM.midiInGetDevCaps(i, ref inCaps, System.Runtime.InteropServices.Marshal.SizeOf(typeof(WinMM.MidiInCaps)));
                devices.Add(new MidiInDevice(i, inCaps));
            }

            return devices.AsReadOnly();
        }        

        public delegate void MidiInHandler(MidiInDevice sender, MidiMessage message);

        public void Open(MidiInHandler callback)
        {
            proc = new WinMM.MidiInProc((int h, uint msg, uint instance, uint param1, uint param2) => callback(this, new MidiMessage(param1, param2)));
            WinMM.midiInOpen(ref handle, Id, proc, 0, WinMM.CALLBACK_FUNCTION);
            opened = true;
        }

        public void Start()
        {
            WinMM.midiInStart(handle);
            started = true;
        }

        public void Stop()
        {
            WinMM.midiInStop(handle);
            started = false;
        }

        public void Close()
        {
            if (started)
            {
                Stop();
            }

            WinMM.midiInClose(handle);
            opened = false;
        }

        public void Dispose()
        {
            if (opened)
            {
                Close();
            }
        }
    }
}
