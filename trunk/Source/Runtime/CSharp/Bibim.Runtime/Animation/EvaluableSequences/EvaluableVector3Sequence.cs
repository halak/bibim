using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 's', 'v', '3')]
    public sealed class EvaluableVector3Sequence : EvaluableSequenceTemplate<Vector3, Vector3Sequence>
    {
        protected override Vector3 Interpolate(Vector3 a, Vector3 b, float t)
        {
            Vector3 result = Vector3.Zero;
            result.X = a.X + (b.X - a.X) * t;
            result.Y = a.Y + (b.Y - a.Y) * t;
            return result;
        }
    }
}