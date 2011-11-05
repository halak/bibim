using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;

namespace Bibim.Animation
{
    public abstract class EvalTreeTemplate<T> : GameAsset
    {
        #region Properties
        public Eval<T> Root
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        protected EvalTreeTemplate()
            : this(null)
        {
        }

        protected EvalTreeTemplate(Eval<T> root)
        {
            Root = root;
        }
        #endregion
    }
}
