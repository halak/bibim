using System;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'b', '_')]
    public sealed class EvalBoolVariable : EvalVariableTemplate<bool>
    {
        #region Constructors
        public EvalBoolVariable()
        {
        }

        public EvalBoolVariable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
