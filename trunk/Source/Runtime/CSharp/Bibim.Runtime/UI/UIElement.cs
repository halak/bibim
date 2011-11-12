using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.UI
{
    public abstract class UIElement : GameComponent
    {
        #region Static Fields
        public static readonly int UnspecifiedID = -1;
        #endregion

        #region Fields
        private int id;
        private string name;
        #endregion

        #region Properties
        public int ID
        {
            get { return id; }
            set
            {
                id = value;
            }
        }

        public string Name
        {
            get { return name; }
            set
            {
                name = value ?? string.Empty;
            }
        }
        #endregion

        #region Constructors
        public UIElement()
            : this(UnspecifiedID, string.Empty)
        {
        }

        public UIElement(int id)
            : this(id, string.Empty)
        {
        }

        public UIElement(int id, string name)
        {
            this.id = id;
            this.name = name ?? string.Empty;
        }
        #endregion
    }
}
