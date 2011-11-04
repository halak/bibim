using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'v', '4')]
    public sealed class EvaluableVector4Variable : EvaluableVariableTemplate<Vector4>
    {
        #region Constructors
        public EvaluableVector4Variable()
        {
        }

        public EvaluableVector4Variable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
