using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    public abstract class Evaluable<T> : GameComponent
    {
        public abstract T Evaluate(EvaluationContext context);
    }
}
