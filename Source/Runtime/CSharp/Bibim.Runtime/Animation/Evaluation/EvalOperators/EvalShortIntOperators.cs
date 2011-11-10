using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 'N', 's', 'i')]
    public sealed class EvalIntToShortInt : EvalUnaryOperatorTemplate<short, int>
    {
        protected override short Calculate(int value) { return (short)value; }
    }
}
