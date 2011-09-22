using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Asset.Pipeline
{
    public abstract class CookableItem<TOutput> : ICookable<TOutput>
    {
        #region Constructors
        protected CookableItem()
        {
        }
        #endregion

        #region Methods
        public abstract TOutput Cook(CookingContext context);

        object ICookable.Cook(CookingContext context)
        {
            return (object)this.Cook(context);
        }
        #endregion
    }
}
