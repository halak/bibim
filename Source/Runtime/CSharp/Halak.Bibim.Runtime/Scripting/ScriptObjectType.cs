using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Scripting
{
    public enum ScriptObjectType
    {
        Void,
        Bool,
        Int,
        UInt,
        LongInt,
        Float,
        Color,
        Int2,
        Int3,
        Int4,
        Float2,
        Float3,
        Float4,
        String,
        SharedObject,
        LightObject,
        Vector2 = Float2,
        Vector3 = Float3,
        Vector4 = Float4,
    }
}
