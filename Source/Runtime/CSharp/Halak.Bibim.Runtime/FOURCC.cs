using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim
{
    public static class FOURCC
    {
        public static uint Make(char a, char b, char c, char d)
        {
            uint a_ = (uint)a;
            uint b_ = (uint)b;
            uint c_ = (uint)c;
            uint d_ = (uint)d;

            return (a_ << 24) | (b_ << 16) | (c_ << 8) | (d_ << 0);
        }
    }
}
