using System;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'b', '_')]
    public sealed class EvaluableBoolVariable : EvaluableVariableTemplate<bool>
    {
        #region Constructors
        public EvaluableBoolVariable()
        {
        }

        public EvaluableBoolVariable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
