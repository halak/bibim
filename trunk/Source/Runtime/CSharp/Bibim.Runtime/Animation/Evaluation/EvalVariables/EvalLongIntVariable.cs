using System;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'l', '_')]
    public sealed class EvalLongIntVariable : EvalVariableTemplate<long>
    {
        #region Constructors
        public EvalLongIntVariable()
        {
        }

        public EvalLongIntVariable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
