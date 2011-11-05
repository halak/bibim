using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.UI
{
    public abstract class UIElement : GameComponent
    {
        #region Fields
        private string name;
        #endregion

        #region Properties
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
            : base(id)
        {
            this.name = name ?? string.Empty;
        }
        #endregion
    }
}
