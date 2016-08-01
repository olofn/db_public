using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace Midi
{
    class WinMM
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct MidiInCaps
        {
            public short MID;
            public short PID;
            public int DriverVersion;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
            public string Name;
            public int Support;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct MidiOutCaps
        {
            public short MID;
            public short PID;
            public int DriverVersion;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
            public string Name;
            public short Technology;
            public short Voices;
            public short Notes;
            public ushort ChannelMask;
            public int Support;
        }; 


        [DllImport("winmm.dll")]
        public static extern int midiInGetDevCaps(int deviceID, ref MidiInCaps caps, int capsSize);

        [DllImport("winmm.dll")]
        public static extern int midiOutGetDevCaps(int deviceID, ref MidiOutCaps caps, int capsSize);

        [DllImport("winmm.dll")]
        public static extern uint midiInGetNumDevs();

        [DllImport("winmm.dll")]
        public static extern uint midiOutGetNumDevs();

        [DllImport("winmm.dll")]
        public static extern int midiInOpen(ref int handle, int deviceID, MidiInProc proc, int instance, int flags);

        [DllImport("winmm.dll")]
        public static extern int midiInClose(int handle);

        [DllImport("winmm.dll")]
        public static extern int midiInStart(int handle);

        [DllImport("winmm.dll")]
        public static extern int midiInStop(int handle);

        [DllImport("winmm.dll")]
        public static extern int midiInReset(int handle);

        public delegate void MidiInProc(int handle, uint msg, uint instance, uint param1, uint param2);

        public const int CALLBACK_FUNCTION = 196608;
    }
}
