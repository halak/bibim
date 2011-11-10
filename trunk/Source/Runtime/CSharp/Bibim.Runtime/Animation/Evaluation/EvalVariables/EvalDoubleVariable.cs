using System;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'd', '_')]
    public sealed class EvalDoubleVariable : EvalVariableTemplate<double>
    {
        #region Constructors
        public EvalDoubleVariable()
        {
        }

        public EvalDoubleVariable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
