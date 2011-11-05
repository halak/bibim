using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Graphics
{
    public sealed class ShaderEffectCookingTag
    {
        public byte[] Buffer
        {
            get;
            set;
        }

        public ShaderEffectCookingTag()
        {
            Buffer = null;
        }

        public ShaderEffectCookingTag(byte[] buffer)
        {
            Buffer = buffer;
        }
    }
}
