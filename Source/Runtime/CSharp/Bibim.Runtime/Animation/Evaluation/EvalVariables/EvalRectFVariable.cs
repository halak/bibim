using System;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'R', 'f')]
    public sealed class EvalRectFVariable : EvalVariableTemplate<RectangleF>
    {
        #region Constructors
        public EvalRectFVariable()
        {
        }

        public EvalRectFVariable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
