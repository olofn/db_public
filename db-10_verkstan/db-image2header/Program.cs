using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.IO;

namespace Image2Header
{
    class Program
    {
        static String byte2HexString(byte b)
        {
            if (b < 10)
                return "0x0" + b.ToString("X");
            else
                return "0x" + b.ToString("X");
        }

        static void Main(string[] args)
        {
            if (args.Length == 0)
            {
                System.Console.WriteLine("You must supply a filename to an image!");
                return;
            }

            String filename = args[0];
            System.Console.WriteLine("Opening image '" + filename + "'");
            Bitmap bitmap = new Bitmap(filename);

            System.Console.WriteLine("Reading image data");
            List<int> bytes = new List<int>();
            Color black = Color.FromArgb(255, 0, 0, 0);
            for (int y = 0; y < bitmap.Height; y++)
            {
                for (int x = 0; x < bitmap.Width; x++)
                {
                    if (bitmap.GetPixel(x, y) == black)
                        bytes.Add(0);
                    else
                        bytes.Add(1);
                }
            }

            System.Console.WriteLine("Writing header file '" + filename + ".hpp'");

            TextWriter tw = new StreamWriter(filename + ".hpp");

            tw.WriteLine("int width = " + bitmap.Width + ";");
            tw.WriteLine("int height = " + bitmap.Height + ";");
            tw.WriteLine("unsigned char data[] = {");
      
            for(int i = 0; i < bytes.Count; i++)
            {
                tw.Write(byte2HexString((byte)bytes[i]));

                if (i != (bytes.Count - 1))
                    tw.Write(",");

                if ((i + 1) % 10 == 0)
                    tw.WriteLine();
            }

            tw.WriteLine("};");
            tw.Close();

            bitmap.Dispose();

            System.Console.WriteLine("All done!");
        }
    }
}
