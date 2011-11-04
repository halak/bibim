using System;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'd', '_')]
    public sealed class EvaluableDoubleVariable : EvaluableVariableTemplate<double>
    {
        #region Constructors
        public EvaluableDoubleVariable()
        {
        }

        public EvaluableDoubleVariable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
