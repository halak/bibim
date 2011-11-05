using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim
{
    public abstract class GameComponent
    {
        #region Static Fields
        public static readonly int UnspecifiedID = -1;
        #endregion

        #region Fields
        private int id;
        #endregion

        #region Properties
        public int ID
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

        public int ClassID
        {
            get { return ClassIDAttribute.GetClassID(GetType()); }
        }
        #endregion

        #region Constructors
        protected GameComponent()
            : this(UnspecifiedID)
        {
        }

        protected GameComponent(int id)
        {
            this.id = id;
        }
        #endregion
    }
}
