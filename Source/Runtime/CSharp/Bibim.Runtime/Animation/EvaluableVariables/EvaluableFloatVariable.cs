using System;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'f', '_')]
    public sealed class EvaluableFloatVariable : EvaluableVariableTemplate<float>
    {
        #region Constructors
        public EvaluableFloatVariable()
        {
        }

        public EvaluableFloatVariable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
