using System;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 's', '_')]
    public sealed class EvaluableShortIntVariable : EvaluableVariableTemplate<short>
    {
        #region Constructors
        public EvaluableShortIntVariable()
        {
        }

        public EvaluableShortIntVariable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
