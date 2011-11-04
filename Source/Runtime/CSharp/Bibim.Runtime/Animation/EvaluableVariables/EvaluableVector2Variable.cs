using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'v', '2')]
    public sealed class EvaluableVector2Variable : EvaluableVariableTemplate<Vector2>
    {
        #region Constructors
        public EvaluableVector2Variable()
        {
        }

        public EvaluableVector2Variable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
