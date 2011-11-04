using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'v', '3')]
    public sealed class EvaluableVector3Variable : EvaluableVariableTemplate<Vector3>
    {
        #region Constructors
        public EvaluableVector3Variable()
        {
        }

        public EvaluableVector3Variable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
