using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'v', '4')]
    public sealed class EvalVector4Variable : EvalVariableTemplate<Vector4>
    {
        #region Constructors
        public EvalVector4Variable()
        {
        }

        public EvalVector4Variable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
