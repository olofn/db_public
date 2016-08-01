using System;
using System.Collections.Generic;
using System.Text;

namespace DB.Audio
{
    public class AudioDevice : IDisposable
    {
        Internal.WaveFormat format;
        Internal.WaveOutPlayer player;

        public int SampleRate { get { return format.nSamplesPerSec; } }

        public IAudioSource AudioSource = null;

        public AudioDevice()
            : this(44100, 16, 16384)
        {
        }

        public AudioDevice(int sampleRate, int bits, int bufferSize)
        {
            format = new Internal.WaveFormat(sampleRate, bits, 2);
            player = new Internal.WaveOutPlayer(-1, format, bufferSize, 2, new Internal.BufferFillEventHandler(FillInternalBuffer));            
        }

        void FillInternalBuffer(IntPtr data, int size)
        {
            int numSamples = size / ((format.wBitsPerSample / 8) * format.nChannels);

            float[] lData = new float[numSamples];
            float[] rData = new float[numSamples];

            FillExternalBuffer(lData, rData, numSamples);

            unchecked
            {
                byte[] b = new byte[size];

                if (format.wBitsPerSample == 16 && format.nChannels == 2)
                {
                    for (int i = 0; i < numSamples; i++)
                    {
                        int l = Math.Min(Math.Max((int)(lData[i] * 32768.0f), short.MinValue), short.MaxValue);
                        int r = Math.Min(Math.Max((int)(rData[i] * 32768.0f), short.MinValue), short.MaxValue);

                        // Left channel
                        b[(i * 4) + 0] = (byte)l; // LSB
                        b[(i * 4) + 1] = (byte)(l >> 8); // MSB

                        // Right channel
                        b[(i * 4) + 2] = (byte)r; // LSB
                        b[(i * 4) + 3] = (byte)(r >> 8); // MSB
                    }
                }
                else
                {
                    throw new Exception("Audio format not yet supported");
                }

                System.Runtime.InteropServices.Marshal.Copy(b, 0, data, size);
            }
        }

        void FillExternalBuffer(float[] left, float[] right, int size)
        {
            if (AudioSource == null || !AudioSource.IsPlaying)
            {
                for (int i = 0; i < size; i++)
                {
                    left[i] = 0.0f; 
                    right[i] = 0.0f;
                }
            }
            else
            {
                AudioSource.Fill(left, right, size);
            }
        }

        public void Dispose()
        {
            player.Dispose();
        }
    }
}
