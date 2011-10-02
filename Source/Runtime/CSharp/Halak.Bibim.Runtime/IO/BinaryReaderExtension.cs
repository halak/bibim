using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Halak.Bibim.IO
{
    public static class BinaryReaderExtension
    {
        public static string ReadBibimString(this BinaryReader reader)
        {
            int length = reader.ReadInt32();
            if (length > 0)
                return Encoding.UTF8.GetString(reader.ReadBytes(length));
            else
                return string.Empty;
        }
    }
}
