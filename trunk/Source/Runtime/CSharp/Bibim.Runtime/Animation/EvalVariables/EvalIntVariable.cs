using System;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'i', '_')]
    public sealed class EvalIntVariable : EvalVariableTemplate<int>
    {
        #region Constructors
        public EvalIntVariable()
        {
        }

        public EvalIntVariable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
