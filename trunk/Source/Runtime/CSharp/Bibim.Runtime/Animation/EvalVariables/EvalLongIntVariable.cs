using System;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'l', '_')]
    public sealed class EvalLongVariable : EvalVariableTemplate<long>
    {
        #region Constructors
        public EvalLongVariable()
        {
        }

        public EvalLongVariable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
