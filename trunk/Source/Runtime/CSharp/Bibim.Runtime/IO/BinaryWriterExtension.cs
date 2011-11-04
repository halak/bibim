using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using Microsoft.Xna.Framework;

namespace Bibim.IO
{
    public static class BinaryWriterExtension
    {
        public static void Write(this BinaryWriter writer, Point value)
        {
            writer.Write(value.X);
            writer.Write(value.Y);
        }

        public static void Write(this BinaryWriter writer, Rectangle value)
        {
            writer.Write(value.X);
            writer.Write(value.Y);
            writer.Write(value.Width);
            writer.Write(value.Height);
        }

        public static void Write(this BinaryWriter writer, RectangleF value)
        {
            writer.Write(value.X);
            writer.Write(value.Y);
            writer.Write(value.Width);
            writer.Write(value.Height);
        }

        public static void Write(this BinaryWriter writer, Vector2 value)
        {
            writer.Write(value.X);
            writer.Write(value.Y);
        }

        public static void Write(this BinaryWriter writer, Vector3 value)
        {
            writer.Write(value.X);
            writer.Write(value.Y);
            writer.Write(value.Z);
        }

        public static void Write(this BinaryWriter writer, Vector4 value)
        {
            writer.Write(value.X);
            writer.Write(value.Y);
            writer.Write(value.Z);
            writer.Write(value.W);
        }

        public static void Write(this BinaryWriter writer, Color value)
        {
            writer.Write(value.R);
            writer.Write(value.G);
            writer.Write(value.B);
            writer.Write(value.A);
        }

        public static void WriteBibimString(this BinaryWriter writer, string value)
        {
            if (string.IsNullOrEmpty(value) == false)
            {
                byte[] bytes = Encoding.UTF8.GetBytes(value);
                writer.Write(bytes.Length);
                writer.Write(bytes);
            }
            else
                writer.Write((int)0);
        }
    }
}
