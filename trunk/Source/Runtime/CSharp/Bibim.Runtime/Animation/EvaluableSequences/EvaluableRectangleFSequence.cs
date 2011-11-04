using System;

namespace Bibim.Animation
{
    [ClassID('e', 's', 'R', 'f')]
    public sealed class EvaluableRectangleFSequence : EvaluableSequenceTemplate<RectangleF, RectangleFSequence>
    {
        protected override RectangleF Interpolate(RectangleF a, RectangleF b, float t)
        {
            RectangleF result = RectangleF.Empty;
            result.X = (int)((float)a.X + ((float)(b.X - a.X)) * t);
            result.Y = (int)((float)a.Y + ((float)(b.Y - a.Y)) * t);
            result.Width = (int)((float)a.Width + ((float)(b.Width - a.Width)) * t);
            result.Height = (int)((float)a.Height + ((float)(b.Height - a.Height)) * t);
            return result;
        }
    }
}