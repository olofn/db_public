using System;
using System.Collections.Generic;
using System.Text;

namespace DB.Audio
{
    public interface IAudioFX
    {
        void Process(float[] left, float[] right, int size);
    }
}
