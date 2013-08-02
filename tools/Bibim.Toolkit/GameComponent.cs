using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim
{
    public abstract class GameComponent
    {        
        #region Properties
        public int ClassID
        {
            get { return ClassIDAttribute.GetClassID(GetType()); }
        }
        #endregion

        #region Constructors
        protected GameComponent()
        {
        }
        #endregion
    }
}
