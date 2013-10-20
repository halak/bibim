using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Bibim.Asset;

namespace Bibim.GFX
{
    [ClassID('A', 'S', 'P', 'K')]
    public sealed class Spark : GameAsset
    {
        #region Fields
        private string descriptor;
        #endregion

        #region Properties
        public string Descriptor
        {
            get { return descriptor; }
            set
            {
                descriptor = value ?? string.Empty;
            }
        }
        #endregion

        #region Constructors
        public Spark()
            : this(null)
        {
        }

        public Spark(string descriptor)
        {
            Descriptor = descriptor;
        }
        #endregion
    }
}
