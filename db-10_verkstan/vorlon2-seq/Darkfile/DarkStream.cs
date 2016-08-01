using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace DB.Darkfile
{
    public interface IChunkReader
    {
        void ReadChunk(string id, long length, DarkInStream stream);
    }

    public class DarkInStream
    {
        private Stream stream;
        private long currentChunkStart;
        private long currentChunkLength;

        public DarkInStream(Stream stream)
        {
            if (!stream.CanRead)
            {
                throw new Exception("Stream not readable");
            }

            if (!stream.CanSeek)
            {
                throw new Exception("Stream not seekable");
            }

            this.stream = stream;
        }

        public delegate void ChunkHandler(string id, long length, DarkInStream stream);

        private class ChunkHandlerWrapper : IChunkReader
        {
            private ChunkHandler handler;

            public ChunkHandlerWrapper(ChunkHandler handler)
            {
                this.handler = handler;
            }

            public void ReadChunk(string id, long length, DarkInStream stream)
            {
                handler(id, length, stream);
            }
        }

        public void ReadChunk(ChunkHandler handler)
        {
            ReadChunk(new ChunkHandlerWrapper(handler));
        }

        public void ReadChunk(IChunkReader reader)
        {
            byte[] idBytes = ReadByteArray(4);

            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < 4; i++)
            {
                char c = (char)idBytes[i];
                if (c >= 'A' && c <= 'Z')
                {
                    sb.Append(c);
                }
                else
                {
                    throw new Exception("Chunk id contained unexpected letter");
                }
            }

            string id = sb.ToString();

            //System.Console.WriteLine("Reading " + id);

            long chunkLength = ReadLong();
            long chunkStart = stream.Position;

            currentChunkStart = chunkStart;
            currentChunkLength = chunkLength;

            reader.ReadChunk(id, chunkLength, this);

            long bytesReadByReader = stream.Position - chunkStart;

            if (bytesReadByReader > chunkLength)
            {
                throw new Exception("Chunk reader read past the end of chunk '" + id + "'");
            }

            //System.Console.WriteLine("Skipping " + (chunkLength - bytesReadByReader));

            // Skip the rest of the chunk
            stream.Seek(chunkLength - bytesReadByReader, SeekOrigin.Current);
        }

        public void ReadAllChunks(ChunkHandler handler)
        {
            ReadAllChunks(new ChunkHandlerWrapper(handler));
        }
        
        public void ReadAllChunks(IChunkReader reader)
        {
            long start = currentChunkStart;
            long length = currentChunkLength;

            while (stream.Position < start + length)
            {
                ReadChunk(reader);
            }
        }

        public byte[] ReadByteArray(int size)
        {
            byte[] b = new byte[size];
            int bytesRead = stream.Read(b, 0, b.Length);
            if (bytesRead != b.Length)
            {
                throw new Exception("Unexpected end of file");
            }

            return b;
        }

        public void ReadByteArray(byte[] b)
        {
            int bytesRead = stream.Read(b, 0, b.Length);
            if (bytesRead != b.Length)
            {
                throw new Exception("Unexpected end of file");
            }
        }

        public void Close()
        {
            stream.Flush();
            if (stream.Position != stream.Length)
            {
                throw new Exception("Data still left in stream");
            }
            stream.Close();
        }

        #region Primitive read functions
        public void Read(out long i)
        {
            i = BitConverter.ToInt64(ReadByteArray(sizeof(long)), 0);
        }

        public void Read(out ulong i)
        {
            i = BitConverter.ToUInt64(ReadByteArray(sizeof(ulong)), 0);
        }

        public void Read(out int i)
        {
            i = BitConverter.ToInt32(ReadByteArray(sizeof(int)), 0);
        }

        public void Read(out uint i)
        {
            i = BitConverter.ToUInt32(ReadByteArray(sizeof(uint)), 0);
        }

        public void Read(out short i)
        {
            i = BitConverter.ToInt16(ReadByteArray(sizeof(short)), 0);
        }

        public void Read(out ushort i)
        {
            i = BitConverter.ToUInt16(ReadByteArray(sizeof(ushort)), 0);
        }

        public void Read(out char i)
        {
            i = BitConverter.ToChar(ReadByteArray(sizeof(char)), 0);
        }

        public void Read(out byte i)
        {
            i = ReadByteArray(sizeof(byte))[0];
        }

        public void Read(out sbyte i)
        {
            i = (sbyte)ReadByteArray(sizeof(sbyte))[0];
        }

        public void Read(out float i)
        {
            i = BitConverter.ToSingle(ReadByteArray(sizeof(float)), 0);
        }

        public void Read(out double i)
        {
            i = BitConverter.ToDouble(ReadByteArray(sizeof(double)), 0);
        }

        public void Read(out bool i)
        {
            i = BitConverter.ToBoolean(ReadByteArray(sizeof(bool)), 0);
        }

        public void Read(out string i)
        {
            int length;
            Read(out length);
            StringBuilder sb = new StringBuilder();
            for (int j = 0; j < length; j++)
            {
                char c;
                Read(out c);
                sb.Append(c);
            }
            i = sb.ToString();
        }

        public long ReadLong() { long i; Read(out i); return i; }
        public ulong ReadULong() { ulong i; Read(out i); return i; }
        public int ReadInt() { int i; Read(out i); return i; }
        public uint ReadUInt() { uint i; Read(out i); return i; }
        public short ReadShort() { short i; Read(out i); return i; }
        public ushort ReadUShort() { ushort i; Read(out i); return i; }
        public char ReadChar() { char i; Read(out i); return i; }
        public byte ReadByte() { byte i; Read(out i); return i; }
        public sbyte ReadSByte() { sbyte i; Read(out i); return i; }
        public float ReadFloat() { float i; Read(out i); return i; }
        public double ReadDouble() { double i; Read(out i); return i; }
        public bool ReadBool() { bool i; Read(out i); return i; }
        public string ReadString() { string i; Read(out i); return i; }

        #endregion
    }

    public class DarkOutStream
    {
        private Stream stream;
        private Stack<long> chunkStarts = new Stack<long>();

        public DarkOutStream(Stream stream)
        {
            if (!stream.CanWrite)
            {
                throw new Exception("Stream not writable");
            }

            if (!stream.CanSeek)
            {
                throw new Exception("Stream not seekable");
            }

            this.stream = stream;
        }

        public void OpenChunk(string id)
        {
            if (id.Length != 4)
            {
                throw new Exception("Id tag must be 4 characters '" + id + "'");
            }

            byte[] idBytes = new byte[4];

            for (int i = 0; i < 4; i++)
            {
                if (id[i] >= 'A' && id[i] <= 'Z')
                {
                    Write((byte)id[i]);
                }
                else
                {
                    throw new Exception("Id tag contains illegal characters, must be A-Z '" + id + "'");
                }
            }

            Write((long)0);
            chunkStarts.Push(stream.Position);
        }

        public void CloseChunk()
        {
            if (chunkStarts.Count == 0)
            {
                throw new Exception("No chunks left to close");
            }

            long currentPos = stream.Position;
            long chunkStart = chunkStarts.Pop();
            long length = currentPos - chunkStart;
            stream.Position = chunkStart - sizeof(long);
            Write(length);
            stream.Position = currentPos;
        }

        public void Close()
        {
            if (chunkStarts.Count != 0)
            {
                throw new Exception("All chunks has not been closed");
            }

            stream.Close();
        }

        #region Primitive write functions

        public void Write(long i)
        {
            byte[] bytes = BitConverter.GetBytes(i);
            stream.Write(bytes, 0, bytes.Length);
        }

        public void Write(ulong i)
        {
            byte[] bytes = BitConverter.GetBytes(i);
            stream.Write(bytes, 0, bytes.Length);
        }

        public void Write(int i)
        {
            byte[] bytes = BitConverter.GetBytes(i);
            stream.Write(bytes, 0, bytes.Length);
        }

        public void Write(uint i)
        {
            byte[] bytes = BitConverter.GetBytes(i);
            stream.Write(bytes, 0, bytes.Length);
        }

        public void Write(short i)
        {
            byte[] bytes = BitConverter.GetBytes(i);
            stream.Write(bytes, 0, bytes.Length);
        }

        public void Write(ushort i)
        {
            byte[] bytes = BitConverter.GetBytes(i);
            stream.Write(bytes, 0, bytes.Length);
        }

        public void Write(char i)
        {
            byte[] bytes = BitConverter.GetBytes(i);
            stream.Write(bytes, 0, bytes.Length);
        }

        public void Write(byte i)
        {
            stream.WriteByte(i);
        }

        public void Write(sbyte i)
        {
            byte[] bytes = BitConverter.GetBytes(i);
            stream.Write(bytes, 0, bytes.Length);
        }

        public void Write(float i)
        {
            byte[] bytes = BitConverter.GetBytes(i);
            stream.Write(bytes, 0, bytes.Length);
        }

        public void Write(double i)
        {
            byte[] bytes = BitConverter.GetBytes(i);
            stream.Write(bytes, 0, bytes.Length);
        }

        public void Write(bool i)
        {
            byte[] bytes = BitConverter.GetBytes(i);
            stream.Write(bytes, 0, bytes.Length);
        }

        public void Write(string i)
        {
            Write(i.Length);
            foreach (char c in i.ToCharArray())
            {
                Write(c);
            }
        }

        public void WriteByteArray(byte[] b)
        {
            stream.Write(b, 0, b.Length);
        }

        public void WriteByteArray(byte[] b, int offset, int length)
        {
            stream.Write(b, offset, length);
        }
        #endregion
    }
}
