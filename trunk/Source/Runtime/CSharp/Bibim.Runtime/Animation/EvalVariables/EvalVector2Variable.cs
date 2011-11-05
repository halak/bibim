using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'v', '2')]
    public sealed class EvalVector2Variable : EvalVariableTemplate<Vector2>
    {
        #region Constructors
        public EvalVector2Variable()
        {
        }

        public EvalVector2Variable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
