using System;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'i', '_')]
    public sealed class EvaluableIntVariable : EvaluableVariableTemplate<int>
    {
        #region Constructors
        public EvaluableIntVariable()
        {
        }

        public EvaluableIntVariable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
