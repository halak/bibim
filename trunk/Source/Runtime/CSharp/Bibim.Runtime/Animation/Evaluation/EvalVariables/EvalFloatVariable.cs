using System;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'f', '_')]
    public sealed class EvalFloatVariable : EvalVariableTemplate<float>
    {
        #region Constructors
        public EvalFloatVariable()
        {
        }

        public EvalFloatVariable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
