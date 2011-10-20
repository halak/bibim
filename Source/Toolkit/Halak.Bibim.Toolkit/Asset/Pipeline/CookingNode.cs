using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Asset.Pipeline
{
    public abstract class CookingNode
    {
        #region Constructor
        protected CookingNode()
        {
        }
        #endregion

        #region Method
        public abstract object CookObject(CookingContext context);
        #endregion
    }

    public abstract class CookingNode<T> : CookingNode
    {
        #region Constructor
        protected CookingNode()
        {
        }
        #endregion

        #region Methods
        public abstract T Cook(CookingContext context);

        public override object CookObject(CookingContext context)
        {
            return (object)this.Cook(context);
        }
        #endregion
    }
}
