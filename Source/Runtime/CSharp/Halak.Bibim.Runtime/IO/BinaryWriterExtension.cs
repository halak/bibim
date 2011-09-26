using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace Halak.Bibim.IO
{
    public static class BinaryWriterExtension
    {
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
