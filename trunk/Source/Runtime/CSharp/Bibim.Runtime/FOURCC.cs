using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;

namespace Bibim
{
    public static class FOURCC
    {
        public static int Make(char a, char b, char c, char d)
        {
            uint a_ = (uint)a;
            uint b_ = (uint)b;
            uint c_ = (uint)c;
            uint d_ = (uint)d;

            Debug.Assert(IsOneByteChar(a));
            Debug.Assert(IsOneByteChar(b));
            Debug.Assert(IsOneByteChar(c));
            Debug.Assert(IsOneByteChar(d));

            return (int)((a_ << 24) | (b_ << 16) | (c_ << 8) | (d_ << 0));
        }

        /// <summary>
        /// 입력한 문자가 1-byte 문자인지 확인합니다.
        /// </summary>
        /// <param name="c">문자</param>
        /// <returns>1-byte 문자 여부 (A-z, a-z, 0-9 외 1-byte 특수 문자)</returns>
        private static bool IsOneByteChar(char c)
        {
            return (uint)byte.MinValue <= c && c <= (uint)byte.MaxValue;
        }
    }
}
