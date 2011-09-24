using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Asset
{
    public sealed partial class PhotoshopDocument
    {
        public sealed class Reader : BinaryReader
        {
            #region Constructor
            public Reader(Stream input)
                : base(input)
            {
            }
            #endregion

            #region Read
            public override short ReadInt16()
            {
                return BitConverter.ToInt16(ReadAdaptiveBytes(2), 0);
            }

            public override int ReadInt32()
            {
                return BitConverter.ToInt16(ReadAdaptiveBytes(4), 0);
            }

            public override long ReadInt64()
            {
                return BitConverter.ToInt64(ReadAdaptiveBytes(8), 0);
            }

            public override ushort ReadUInt16()
            {
                return BitConverter.ToUInt16(ReadAdaptiveBytes(2), 0);
            }

            public override uint ReadUInt32()
            {
                return BitConverter.ToUInt32(ReadAdaptiveBytes(4), 0);
            }

            public override ulong ReadUInt64()
            {
                return BitConverter.ToUInt64(ReadAdaptiveBytes(8), 0);
            }

            public string ReadPascalString()
            {
                byte stringLength = base.ReadByte();

                char[] c = base.ReadChars(stringLength);

                if ((stringLength % 2) == 0)
                    base.ReadByte();

                return new string(c);
            }

            public string ReadPSDString()
            {
                byte stringLength = base.ReadByte();
                byte[] psdString = base.ReadBytes(stringLength);

                return Encoding.Default.GetString(psdString);
            }

            public Rectangle ReadRectangle()
            {
                Rectangle result = Rectangle.Empty;
                result.Y = ReadInt32();
                result.X = ReadInt32();
                result.Height = ReadInt32() - result.Y;
                result.Width = ReadInt32() - result.X;
                return result;
            }

            public byte[] ReadRawPixelData(int width, int height, int bitsPerPixel)
            {
                switch (bitsPerPixel)
                {
                    case 1:
                    case 8:
                        return ReadBytes(width * height);
                    case 16:
                        byte[] result = new byte[width * height];
                        for (int i = 0; i < result.Length; i++)
                            result[i] = (byte)(ReadUInt16() >> 8);

                        return result;
                    default:
                        throw new Exception();
                }
            }

            public byte[] ReadRLECompressedPixelData(int width, int height, int bitsPerPixel)
            {
                byte[] result = new byte[width * height];

                for (int i = 0, bitmapOffset = 0; i < result.Length; )
                {
                    int length = (int)ReadByte();
                    if (length < 128)
                    {
                        length++;
                        i += length;

                        for (int k = 0; k < length; k++, bitmapOffset++)
                            result[bitmapOffset] = ReadByte();
                    }
                    else if (length > 128)
                    {
                        length ^= 0x0FF;
                        length += 2;
                        i += length;
                        byte compressedValue = ReadByte();

                        for (int k = 0; k < length; k++, bitmapOffset++)
                            result[bitmapOffset] = compressedValue;
                    }
                    // length == 128, 아무것도 안 합니다.
                }

                return result;
            }
            #endregion

            #region ReadAdaptiveBytes
            public byte[] ReadAdaptiveBytes(int count)
            {
                byte[] data = base.ReadBytes(count);
                Swap(data);
                return data;
            }
            #endregion

            #region Swap
            private static void Swap(byte[] data)
            {
                for (int i = 0; i < data.Length / 2; i++)
                {
                    byte t = data[i];
                    data[i] = data[data.Length - i - 1];
                    data[data.Length - i - 1] = t;
                }
            }
            #endregion
        }
    }
}
