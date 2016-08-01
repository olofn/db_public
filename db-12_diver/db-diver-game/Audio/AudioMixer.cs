using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.CompilerServices;

namespace DB.Audio
{
    public class AudioMixer : IAudioSource
    {
        public class Channel
        {
            public Channel(IAudioSource audioSource, float volume, float panning, IAudioFX audioFX)
            {
                AudioSource = audioSource;
                Volume = volume;
                Panning = panning;
                AudioFX = audioFX;
            }

            public IAudioSource AudioSource;            
            public float Volume;
            public float Panning;
            public readonly IAudioFX AudioFX;
        }

        List<Channel> channels = new List<Channel>();

        float[] mixLeft = null;
        float[] mixRight = null;

        public float MasterVolume = 1.0f;
        public IAudioFX MasterAudioFX;
        public readonly int SampleRate;
        public bool IsPlaying { get { return channels.Count > 0; } }

        public static AudioMixer MainMixer;

        public AudioMixer(AudioDevice audioDevice)
        {
            audioDevice.AudioSource = this;
            SampleRate = audioDevice.SampleRate;
            MainMixer = this;
        }

        [MethodImpl(MethodImplOptions.Synchronized)]
        public void Fill(float[] left, float[] right, int size)
        {
            for (int i = 0; i < size; i++)
            {
                left[i] = 0.0f;
                right[i] = 0.0f;
            }

            if (mixLeft == null || mixRight == null || mixLeft.Length != size || mixRight.Length != size)
            {
                mixLeft = new float[size];
                mixRight = new float[size];
            }

            channels.RemoveAll(new Predicate<Channel>(delegate(Channel c) { return !c.AudioSource.IsPlaying; }));

            foreach (Channel c in channels)
            {
                c.AudioSource.Fill(mixLeft, mixRight, size);

                float leftGain = c.Volume * (float)Math.Sqrt(1.0f - c.Panning);
                float rightGain = c.Volume * (float)Math.Sqrt(c.Panning);

                if (c.AudioFX != null)
                {
                    c.AudioFX.Process(mixLeft, mixRight, size);
                }

                for (int i = 0; i < size; i++)
                {
                    left[i] += mixLeft[i] * leftGain * MasterVolume;
                    right[i] += mixRight[i] * rightGain * MasterVolume;
                }
            }

            IAudioFX masterFX = MasterAudioFX;
            if (masterFX != null)
            {
                masterFX.Process(left, right, size);
            }        
        }

        public Channel Play(IAudioSource a)
        {
            return Play(a, 1.0f, 0.5f, null);
        }

        public Channel Play(IAudioSource a, float volume)
        {
            return Play(a, volume, 0.5f, null);
        }

        public Channel Play(IAudioSource a, float volume, float panning)
        {
            return Play(a, volume, panning, null);
        }

        public Channel Play(IAudioSource a, float volume, float panning, IAudioFX audioFX)
        {
            Channel channel = new Channel(a, volume, panning, audioFX);
            Play(channel);
            return channel;
        }

        [MethodImpl(MethodImplOptions.Synchronized)]
        public void Play(Channel channel)
        {
            channels.Add(channel);
        }

        [MethodImpl(MethodImplOptions.Synchronized)]
        public void Stop(Channel channel)
        {
            channels.Remove(channel);
        }
    }
}
