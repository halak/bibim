using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'v', '3')]
    public sealed class EvalVector3Variable : EvalVariableTemplate<Vector3>
    {
        #region Constructors
        public EvalVector3Variable()
        {
        }

        public EvalVector3Variable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
