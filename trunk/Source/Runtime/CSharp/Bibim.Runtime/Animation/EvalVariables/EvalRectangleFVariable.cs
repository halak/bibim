using System;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'R', 'f')]
    public sealed class EvalRectangleFVariable : EvalVariableTemplate<RectangleF>
    {
        #region Constructors
        public EvalRectangleFVariable()
        {
        }

        public EvalRectangleFVariable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
