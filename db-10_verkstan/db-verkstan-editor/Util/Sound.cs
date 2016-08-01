using System;
using System.Runtime.InteropServices;
using System.Resources;
using System.IO;
namespace Win32
{
    public class Winmm
    {
        public const UInt32 SND_ASYNC = 1;
        public const UInt32 SND_MEMORY = 4;
        // these 2 overloads we dont need ...
        // [DllImport("Winmm.dll")]
        // public static extern bool PlaySound(IntPtr rsc, IntPtr hMod, UInt32 dwFlags);

        // [DllImport("Winmm.dll")]
        // public static extern bool PlaySound(string Sound, IntPtr hMod, UInt32 dwFlags);

        // this is the overload we want to play embedded resource...
        [DllImport("Winmm.dll")]
        public static extern bool PlaySound(byte[] data, IntPtr hMod, UInt32 dwFlags);
        public Winmm()
        {
        }
        public static void PlayWavResource(string wav)
        {
            // get the namespace
            string strNameSpace =
            System.Reflection.Assembly.GetExecutingAssembly().GetName().Name.ToString();

            // get the resource into a stream
            Stream str =
            System.Reflection.Assembly.GetExecutingAssembly().GetManifestResourceStream(strNameSpace + "." + wav);
            if (str == null)
                return;
            // bring stream into a byte array
            byte[] bStr = new Byte[str.Length];
            str.Read(bStr, 0, (int)str.Length);
            // play the resource
            PlaySound(bStr, IntPtr.Zero, SND_ASYNC | SND_MEMORY);
        }
    }
}
