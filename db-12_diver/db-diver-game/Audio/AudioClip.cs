using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace DB.Audio
{    
    public class AudioClip
    {
        int channels;
        int rate;
        float[] left = null;
        float[] right = null;

        public int Length { get { return left.Length; } }

        public override string ToString()
        {
            return "[AudioClip channels=" + channels + " rate=" + rate + " length=" + Length + "] " + left[3000];
        }

        public AudioClip(int rate, float[] mono)
        {            
            this.channels = 1;
            this.rate = rate;
            this.left = new float[mono.Length];

            for (int i = 0; i < mono.Length; i++)
            {
                this.left[i] = mono[i];
            }
        }

        public AudioClip(int rate, float[] left, float[] right)
        {
            this.channels = 2;
            this.rate = rate;

            if (left.Length != right.Length)
            {
                throw new Exception("Left and right channels are of different length");
            }

            this.left = new float[left.Length];
            this.right = new float[right.Length];

            for (int i = 0; i < left.Length; i++)
            {
                this.left[i] = left[i];
                this.right[i] = right[i];
            }
        }

        public AudioClip(string fileName): this(new FileStream(fileName, FileMode.Open)) { }

        private static string ReadChunk(BinaryReader reader)
        {
            byte[] ch = new byte[4];
            reader.Read(ch, 0, ch.Length);
            return System.Text.Encoding.ASCII.GetString(ch);
        }

        public AudioClip(Stream stream)
        {
            BinaryReader Reader = new BinaryReader(stream);
            if (ReadChunk(Reader) != "RIFF")
                throw new Exception("Invalid file format");

            Reader.ReadInt32(); // File length minus first 8 bytes of RIFF description, we don't use it

            if (ReadChunk(Reader) != "WAVE")
                throw new Exception("Invalid file format");

            if (ReadChunk(Reader) != "fmt ")
                throw new Exception("Invalid file format");

            int len = Reader.ReadInt32();
            if (len < 16) // bad format chunk length
                throw new Exception("Invalid file format");

            
            Reader.ReadInt16(); // Skip format tag
            channels = Reader.ReadInt16();
            rate = Reader.ReadInt32();
            Reader.ReadInt32(); // Skip bytes per sec
            Reader.ReadInt16(); // Skip block align
            int bits = Reader.ReadInt16();

            // advance in the stream to skip the wave format block 
            len -= 16; // minimum format size
            while (len > 0)
            {
                Reader.ReadByte();
                len--;
            }

            // assume the data chunk is aligned
            while (stream.Position < stream.Length && ReadChunk(Reader) != "data")
                ;

            if (stream.Position >= stream.Length)
                throw new Exception("Invalid file format");

            int length = Reader.ReadInt32() / (channels * (bits / 8));

            left = new float[length];
            
            if (channels == 2)
            {
                right = new float[length];
            }

            //Reader.ReadByte();

            for (int i = 0; i < length; i++)
            {
                if (channels == 1)
                {
                    if (bits == 8)
                    {
                        byte l = Reader.ReadByte();

                        left[i] = (l / 255.0f) * 2.0f - 1.0f;
                    }
                    else if (bits == 16)
                    {
                        ushort l = Reader.ReadUInt16();

                        left[i] = (l / 65535.0f) * 2.0f - 1.0f;
                    }
                    else
                    {
                        throw new Exception("Invalid file format");
                    }
                }
                else if (channels == 2)
                {
                    if (bits == 8)
                    {
                        byte l = Reader.ReadByte();
                        byte r = Reader.ReadByte();

                        left[i] = (l / 255.0f) * 2.0f - 1.0f;
                        right[i] = (r / 255.0f) * 2.0f - 1.0f;
                    }
                    else if (bits == 16)
                    {
                        short l = Reader.ReadInt16();
                        short r = Reader.ReadInt16();

                        left[i] = (l / 32768.0f);
                        right[i] = (r / 32768.0f);
                    }
                    else
                    {
                        throw new Exception("Invalid file format");
                    }
                }
                else
                {
                    throw new Exception("Invalid file format");
                }
            }

            Reader.Close();
        }

        public AudioMixer.Channel Play()
        {
            return Play(1.0f, 0.5f, 1.0f, null, AudioMixer.MainMixer);
        }

        public AudioMixer.Channel Play(float volume)
        {
            return Play(volume, 0.5f, 1.0f, null, AudioMixer.MainMixer);
        }

        public AudioMixer.Channel Play(float volume, float panning)
        {
            return Play(volume, panning, 1.0f, null, AudioMixer.MainMixer);
        }

        public AudioMixer.Channel Play(float volume, float panning, float pitch)
        {
            return Play(volume, panning, pitch, null, AudioMixer.MainMixer);
        }

        public AudioMixer.Channel Play(float volume, float panning, float pitch, IAudioFX audioFX)
        {
            return Play(volume, panning, pitch, audioFX, AudioMixer.MainMixer);
        }

        public AudioMixer.Channel Play(float volume, float panning, float pitch, IAudioFX audioFX, AudioMixer mixer)
        {
            double rate = pitch * ((double)this.rate / mixer.SampleRate);
            return mixer.Play(new AudioClipSource(this, rate), volume, panning, audioFX);
        }

        private class AudioClipSource : IAudioSource
        {
            AudioClip clip;
            double rate;
            double position = 0.0f;

            public AudioClipSource(AudioClip clip, double rate)
            {
                this.clip = clip;
                this.rate = rate;
            }

            public bool IsPlaying { get { return position < clip.Length; } }
            
            public void Fill(float[] left, float[] right, int size)
            {
                for (int i = 0; i < size; i++)
                {
                    if (position < clip.Length-1)
                    {
                        int p = (int)position;
                        float f = (float)(position - p);
                        float l = clip.left[p] * (1.0f - f) + clip.left[p + 1] * f;
                        float r = l;

                        if (clip.channels == 2)
                        {
                            r = clip.right[p] * (1.0f - f) + clip.right[p + 1] * f;
                        }
   
                        left[i] = l;
                        right[i] = r;

                        position += rate;
                    }
                    else
                    {
                        left[i] = 0.0f;
                        right[i] = 0.0f;
                    }
                }
            }
        }
    }
}
