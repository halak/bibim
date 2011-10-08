using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;
using Halak.Bibim.Asset;

namespace Halak.Bibim.Scripting
{
    [ClassID('S', 'C', 'R', 'T')]
    public sealed class Script : GameAsset
    {
        #region Fields
        private List<string> stringTable;
        private ReadOnlyCollection<string> readonlyStringTable;
        #endregion

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

        public IList<string> StringTable
        {
            get { return readonlyStringTable; }
        }
        #endregion

        #region Constructors
        public Script(byte[] buffer, uint entryPoint)
            : this(buffer, entryPoint, null)
        {
        }

        public Script(byte[] buffer, uint entryPoint, IEnumerable<string> stringTable)
        {
            this.Buffer = buffer;
            this.EntryPoint = entryPoint;
            if (stringTable != null)
                this.stringTable = new List<string>(stringTable);
            else
                this.stringTable = new List<string>();
            this.readonlyStringTable = new ReadOnlyCollection<string>(this.stringTable);
        }
        #endregion
    }
}
