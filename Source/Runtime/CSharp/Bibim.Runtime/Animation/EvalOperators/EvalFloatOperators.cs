using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 'N', 'f', '_')]
    public sealed class EvalFloatNegation : EvalUnaryOperatorTemplate<float, float>
    {
        protected override float Calculate(float value) { return -value; }
    }

    [ClassID('e', 'A', 'f', '_')]
    public sealed class EvalFloatAddition : EvalBinaryOperatorTemplate<float, float, float>
    {
        protected override float Calculate(float left, float right) { return left + right; }
    }

    [ClassID('e', 'S', 'f', '_')]
    public sealed class EvalFloatSubtraction : EvalBinaryOperatorTemplate<float, float, float>
    {
        protected override float Calculate(float left, float right) { return left - right; }
    }

    [ClassID('e', 'X', 'f', '_')]
    public sealed class EvalFloatMultiplication : EvalBinaryOperatorTemplate<float, float, float>
    {
        protected override float Calculate(float left, float right) { return left * right; }
    }

    [ClassID('e', 'D', 'f', '_')]
    public sealed class EvalFloatDivision : EvalBinaryOperatorTemplate<float, float, float>
    {
        protected override float Calculate(float left, float right) { return left / right; }
    }

    [ClassID('e', 'M', 'f', '_')]
    public sealed class EvalFloatModulus : EvalBinaryOperatorTemplate<float, float, float>
    {
        protected override float Calculate(float left, float right) { return left % right; }
    }

    [ClassID('e', 'C', 'f', 'i')]
    public sealed class EvalIntToFloat : EvalUnaryOperatorTemplate<float, int>
    {
        protected override float Calculate(int value) { return (float)value; }
    }

    [ClassID('e', 'C', 'f', 'd')]
    public sealed class EvaDoubleToFloat : EvalUnaryOperatorTemplate<float, double>
    {
        protected override float Calculate(double value) { return (float)value; }
    }
}
