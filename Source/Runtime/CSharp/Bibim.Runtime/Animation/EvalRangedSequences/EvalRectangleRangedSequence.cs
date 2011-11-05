using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'r', 'r', '_')]
    public sealed class EvalRectangleRangedSequence : EvalRangedSequenceTemplate<Rectangle, RectangleSequence>
    {
        protected override Rectangle Interpolate(Rectangle a, Rectangle b, float t)
        {
            Rectangle result = Rectangle.Empty;
            result.X = (int)((float)a.X + ((float)(b.X - a.X)) * t);
            result.Y = (int)((float)a.Y + ((float)(b.Y - a.Y)) * t);
            result.Width = (int)((float)a.Width + ((float)(b.Width - a.Width)) * t);
            result.Height = (int)((float)a.Height + ((float)(b.Height - a.Height)) * t);
            return result;
        }
    }
}