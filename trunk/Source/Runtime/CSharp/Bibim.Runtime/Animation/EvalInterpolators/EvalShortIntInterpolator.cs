using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 'I', 's', '_')]
    public sealed class EvalShortIntInterpolator : EvalInterpolatorTemplate<short>
    {
        public override short Interpolate(short a, short b, float t)
        {
            return MathExtension.Lerp(a, b, t);
        }
    }
}
