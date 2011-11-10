using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 'N', 'i', '_')]
    public sealed class EvalIntNegation : EvalUnaryOperatorTemplate<int, int>
    {
        protected override int Calculate(int value) { return -value; }
    }

    [ClassID('e', 'A', 'i', '_')]
    public sealed class EvalIntAddition : EvalBinaryOperatorTemplate<int, int, int>
    {
        protected override int Calculate(int left, int right) { return left + right; }
    }

    [ClassID('e', 'S', 'i', '_')]
    public sealed class EvalIntSubtraction : EvalBinaryOperatorTemplate<int, int, int>
    {
        protected override int Calculate(int left, int right) { return left - right; }
    }

    [ClassID('e', 'X', 'i', '_')]
    public sealed class EvalIntMultiplication : EvalBinaryOperatorTemplate<int, int, int>
    {
        protected override int Calculate(int left, int right) { return left * right; }
    }

    [ClassID('e', 'D', 'i', '_')]
    public sealed class EvalIntDivision : EvalBinaryOperatorTemplate<int, int, int>
    {
        protected override int Calculate(int left, int right) { return left / right; }
    }

    [ClassID('e', 'M', 'i', '_')]
    public sealed class EvalIntModulus : EvalBinaryOperatorTemplate<int, int, int>
    {
        protected override int Calculate(int left, int right) { return left % right; }
    }

    [ClassID('e', 'N', 'i', 's')]
    public sealed class EvalShortIntToInt : EvalUnaryOperatorTemplate<int, short>
    {
        protected override int Calculate(short value) { return (int)value; }
    }

    [ClassID('e', 'N', 'i', 'l')]
    public sealed class EvalLongIntToInt : EvalUnaryOperatorTemplate<int, long>
    {
        protected override int Calculate(long value) { return (int)value; }
    }
}
