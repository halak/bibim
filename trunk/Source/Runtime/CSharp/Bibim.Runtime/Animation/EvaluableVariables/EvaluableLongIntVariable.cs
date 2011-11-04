using System;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'l', '_')]
    public sealed class EvaluableLongVariable : EvaluableVariableTemplate<long>
    {
        #region Constructors
        public EvaluableLongVariable()
        {
        }

        public EvaluableLongVariable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
