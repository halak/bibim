using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 'N', 'd', 'f')]
    public sealed class EvalFloatToDouble : EvalUnaryOperatorTemplate<double, float>
    {
        protected override double Calculate(float value) { return (double)value; }
    }
}
