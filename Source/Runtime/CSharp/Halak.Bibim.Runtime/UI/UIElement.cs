using System;
using System.Collections.Generic;
using System.Text;

namespace Halak.Bibim.UI
{
    public abstract class UIElement
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
        {
            this.name = string.Empty;
        }

        public UIElement(string name)
        {
            this.name = name ?? string.Empty;
        }
        #endregion
    }
}
