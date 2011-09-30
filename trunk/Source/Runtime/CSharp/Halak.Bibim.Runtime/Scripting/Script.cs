using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Halak.Bibim.Asset;

namespace Halak.Bibim.Scripting
{
    public sealed class Script : GameAsset
    {
        #region Properties
        public byte[] Buffer
        {
            get;
            private set;
        }

        public uint EntryPoint
        {
            get;
            private set;
        }
        #endregion

        #region Constructors
        public Script(byte[] buffer, uint entryPoint)
        {
            Buffer = buffer;
            EntryPoint = entryPoint;
        }
        #endregion
    }
}
