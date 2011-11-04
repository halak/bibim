using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 's', 'v', '4')]
    public sealed class EvaluableVector4Sequence : EvaluableSequenceTemplate<Vector4, Vector4Sequence>
    {
        protected override Vector4 Interpolate(Vector4 a, Vector4 b, float t)
        {
            Vector4 result = Vector4.Zero;
            result.X = a.X + (b.X - a.X) * t;
            result.Y = a.Y + (b.Y - a.Y) * t;
            return result;
        }
    }
}