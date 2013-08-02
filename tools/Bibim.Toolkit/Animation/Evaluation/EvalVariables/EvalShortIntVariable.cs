using System;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 's', '_')]
    public sealed class EvalShortIntVariable : EvalVariableTemplate<short>
    {
        #region Constructors
        public EvalShortIntVariable()
        {
        }

        public EvalShortIntVariable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
