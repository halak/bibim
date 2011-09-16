using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace Halak.Bibim.IO
{
    public static class BinaryReaderExtension
    {
        public static string ReadBibimString(this BinaryReader reader)
        {
            int length = reader.ReadInt32();
            return Encoding.UTF8.GetString(reader.ReadBytes(length));
        }
    }
}
