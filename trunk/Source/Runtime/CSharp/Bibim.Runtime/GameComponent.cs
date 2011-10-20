using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim
{
    public abstract class GameComponent
    {
        #region Static Fields
        public static readonly uint UnspecifiedID = 0xFFFFFFFF;
        #endregion

        #region Fields
        private uint id;
        #endregion

        #region Properties
        public uint ID
        {
            get { return id; }
            set
            {
                if (id != value)
                {
                    id = value;
                }
            }
        }
        #endregion

        #region Constructors
        protected GameComponent()
            : this(UnspecifiedID)
        {
        }

        protected GameComponent(uint id)
        {
            this.id = id;
        }
        #endregion
    }
}
