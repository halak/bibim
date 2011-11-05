using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Scripting
{
    public enum ScriptObjectType
    {
        Void,
        Bool,
        Int,
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
        Point2 = Int2,
        Point3 = Int3,
        Point4 = Int4,
        Vector2 = Float2,
        Vector3 = Float3,
        Vector4 = Float4,
    }
}
