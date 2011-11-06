using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 'N', 'l', 'i')]
    public sealed class EvalIntToLongInt : EvalUnaryOperatorTemplate<long, int>
    {
        protected override long Calculate(int value) { return (long)value; }
    }
}
