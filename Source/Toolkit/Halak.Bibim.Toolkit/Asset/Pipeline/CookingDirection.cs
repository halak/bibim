using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Serialization;

namespace Halak.Bibim.Asset.Pipeline
{
    public abstract class CookingDirection
    {
        #region Constructors
        protected CookingDirection()
        {
        }
        #endregion

        #region Methods
        public abstract void Cook(CookingContext context);
        #endregion
    }
}
