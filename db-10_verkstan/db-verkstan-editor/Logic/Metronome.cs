using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VerkstanEditor.Logic
{
    public class Metronome
    {
        #region Properties
        private static int bpm = 120;
        public static int BPM
        {
            get
            {
                return bpm;
            }
            set
            {
                bpm = value;
            }
        }
        public static int TicksPerBeat
        {
            get
            {
                return 256;
            }
        }
        private static int ticks = 1;
        public static int Ticks
        {
            get
            {
                return ticks;
            }
            set
            {
                ticks = value;

                if (ticks < 1)
                    ticks = 1;

                if (tick > ticks)
                {
                    tick = ticks;
                }
            }
        }
        private static int tick = 0;
        public static int Tick
        {
            get
            {
                 if (!ticking)
                    return tick;
    
                int currentSystemTickCount = System.Environment.TickCount;
                int ms = currentSystemTickCount - lastSystemTickCount;
                int tpm = BPM * TicksPerBeat;
                float tps = tpm / 60.0f;
                float tpms = tps / 1000.0f;

                int tickAddition = (int)(tpms * ms) + (int)leftOvers;
                tick += tickAddition;
                leftOvers -= (int)leftOvers;
                leftOvers +=  (tpms * ms) - (int)(tpms * ms);

                lastSystemTickCount = currentSystemTickCount;

                /*
                if (Loop && beat > loopEnd)
                {
                    beat = loopStart;
                }*/
                if (tick > ticks)
                {
                    tick = ticks;
                    ticking = false;
                }

                return tick;
            }
            set
            {
                tick = value;
                lastSystemTickCount = System.Environment.TickCount;
                leftOvers = 0.0f;

                if (tick > ticks)
                    tick = ticks;

                if (tick < 0)
                    tick = 0;
            }
        }
        public static int Milliseconds
        {
            get
            {
    
                float b = Tick / (float)TicksPerBeat;
                return (int)(b / BPM * 60000);
            }
        }
        #endregion

        #region Private Variables
        private static bool ticking = false;
        private static int lastSystemTickCount = 0;
        private static float leftOvers = 0;
        #endregion

        #region Events
        public delegate void BeatChangedHandler(int beat);
        public static event BeatChangedHandler BeatChangedFastUpdate;
        public static event BeatChangedHandler BeatChangedSlowUpdate;
        public static void OnBeatChangedFastUpdate(int beat)
        {
            if (BeatChangedFastUpdate != null)
                BeatChangedFastUpdate(beat);
        }
        public static void OnBeatChangedSlowUpdate(int beat)
        {
            if (BeatChangedSlowUpdate != null)
                BeatChangedSlowUpdate(beat);
        }
        #endregion

        #region Public Static Methods
        public static void Start()
        {
            ticking = true;
            lastSystemTickCount = System.Environment.TickCount;
        }

        public static void Pause()
        {
            ticking = false;
        }
        #endregion
    }
}
