using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 'N', 'b', '_')]
    public sealed class EvalBoolNOT : EvalUnaryOperatorTemplate<bool, bool>
    {
        protected override bool Calculate(bool value) { return !value; }
    }

    [ClassID('e', 'A', 'N', 'b')]
    public sealed class EvalBoolAND : EvalBinaryOperatorTemplate<bool, bool, bool>
    {
        protected override bool Calculate(bool left, bool right) { return left && right; }
    }

    [ClassID('e', 'O', 'R', 'b')]
    public sealed class EvalBoolOR : EvalBinaryOperatorTemplate<bool, bool, bool>
    {
        protected override bool  Calculate(bool left, bool right) { return left || right; }
    }
}
