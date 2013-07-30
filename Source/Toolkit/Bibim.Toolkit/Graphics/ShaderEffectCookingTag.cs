using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Graphics
{
    public sealed class ShaderEffectCookingTag
    {
        public byte[] Code
        {
            get;
            set;
        }

        public int Extra
        {
            get;
            set;
        }

        public ShaderEffectCookingTag()
            : this(null, 0)
        {
        }

        public ShaderEffectCookingTag(byte[] code, int extra)
        {
            Code = code;
            Extra = extra;
        }
    }
}
