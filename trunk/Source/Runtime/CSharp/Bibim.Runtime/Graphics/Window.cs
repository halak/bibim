using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Graphics
{
    public abstract class Window : GameModule
    {
        #region Properties
        public abstract Point2 Position
        {
            get;
            set;
        }

        public abstract Point2 Size
        {
            get;
            set;
        }

        public abstract bool Visible
        {
            get;
            set;
        }
        #endregion

        #region Methods
        public abstract void Close();
        #endregion
    }
}
