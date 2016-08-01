using System;
using System.Collections.Generic;
using System.Text;

namespace DB.Audio
{
    public interface IAudioSource
    {
        bool IsPlaying { get; }

        void Fill(float[] left, float[] right, int size);
    }
}
