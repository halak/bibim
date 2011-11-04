using System;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'R', 'f')]
    public sealed class EvaluableRectangleFVariable : EvaluableVariableTemplate<RectangleF>
    {
        #region Constructors
        public EvaluableRectangleFVariable()
        {
        }

        public EvaluableRectangleFVariable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
