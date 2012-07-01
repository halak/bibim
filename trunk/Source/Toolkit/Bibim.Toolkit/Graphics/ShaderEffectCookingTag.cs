using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Graphics
{
    public sealed class ShaderEffectCookingTag
    {
        public string Code
        {
            get;
            set;
        }

        public ShaderEffectCookingTag()
        {
            Code = string.Empty;
        }

        public ShaderEffectCookingTag(string code)
        {
            Code = code;
        }
    }
}
