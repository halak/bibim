using System;
using System.Collections.Generic;
using System.Text;

namespace Halak.Bibim.UI
{
    public abstract class UIElement
    {
        #region Static Fields
        public const uint UnspecifiedID = 0xFFFFFFFF;
        #endregion

        #region Fields
        private uint id;
        private string name;
        #endregion

        #region Properties
        public uint ClassID
        {
            get { return ClassIDAttribute.GetClassID(GetType()); }
        }

        public uint ID
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

        public UIElement(uint id)
            : this(id, string.Empty)
        {
        }

        public UIElement(uint id, string name)
        {
            this.id = id;
            this.name = name ?? string.Empty;
        }
        #endregion
    }
}
