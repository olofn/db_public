using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Midi
{
    public struct MidiMessage
    {
        public enum Commands
        {
            NoteOn = 9,
            NoteOff = 8,
            Controller = 11,
            PitchWheel = 14,
            Program = 12
        }

        public uint TimeStamp;
        public uint Channel;
        public Commands Command;
        public uint Param1;
        public uint Param2;

        public uint PitchWheelPosition { get { return (Param2 << 7 | Param1); } }

        public MidiMessage(uint message)
            : this(message, 0)
        { }

        public MidiMessage(uint message, uint timestamp)
        {
            this.TimeStamp = timestamp;
            this.Channel = message & 0xf;
            this.Command = (Commands)((message >> 4) & 0xf);
            this.Param1 = (message >> 8) & 0xff;
            this.Param2 = (message >> 16) & 0xff;
        }

        public MidiMessage(uint channel, Commands command, uint param1, uint param2) :
            this(channel, command, param1, param2, 0)
        { }

        public MidiMessage(uint channel, Commands command, uint param1, uint param2, uint timeStamp)
        {
            TimeStamp = timeStamp;
            Channel = channel;
            Command = command;
            Param1 = param1;
            Param2 = param2;
        }

        public uint GetAsUInt()
        {
            return Channel | ((uint)Command << 4) | (Param1 << 8) | (Param2 << 16);
        }

        public override string ToString()
        {
            if (Command == Commands.PitchWheel)
            {
                return "#" + Channel + ": " + Command + " (" + PitchWheelPosition + ")";
            }
            else
            {
                return "#" + Channel + ": " + Command + " (" + Param1 + ", " + Param2 + ")";
            }
        }
    }
}
