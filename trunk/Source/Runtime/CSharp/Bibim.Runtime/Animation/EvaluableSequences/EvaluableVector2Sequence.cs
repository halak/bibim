using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 's', 'v', '2')]
    public sealed class EvaluableVector2Sequence : EvaluableSequenceTemplate<Vector2, Vector2Sequence>
    {
        protected override Vector2 Interpolate(Vector2 a, Vector2 b, float t)
        {
            Vector2 result = Vector2.Zero;
            result.X = a.X + (b.X - a.X) * t;
            result.Y = a.Y + (b.Y - a.Y) * t;
            return result;
        }
    }
}