using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.Xml.Serialization;

namespace Bibim.Animation
{
    public abstract class Eval<T> : GameComponent
    {
        public abstract T Evaluate(EvalContext context);
    }
}
