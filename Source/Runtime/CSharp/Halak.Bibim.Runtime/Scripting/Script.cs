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
        #region Function (Nested Struct)
        public struct Function
        {
            public readonly string Name;
            public readonly int Position;
            public readonly int ArgumentStackSize;
            public readonly ScriptObjectType[] ReturnTypes;
            public readonly ScriptObjectType[] ParameterTypes;

            public Function(string name, int position, int argumentStackSize, ScriptObjectType[] returnTypes, ScriptObjectType[] parameterTypes)
            {
                Name = name;
                Position = position;
                ArgumentStackSize = argumentStackSize;
                ReturnTypes = returnTypes;
                ParameterTypes = parameterTypes;
            }
        }
        #endregion

        #region Fields
        private List<string> stringTable;
        private ReadOnlyCollection<string> readonlyStringTable;
        private readonly Function[] functionTable;
        #endregion

        #region Properties
        public byte[] Buffer
        {
            get;
            private set;
        }

        public IList<string> StringTable
        {
            get { return readonlyStringTable; }
        }

        public Function[] FunctionTable
        {
            get { return functionTable; }
        }
        #endregion

        #region Constructors
        public Script(byte[] buffer, int length)
            : this(buffer, length, null, null)
        {
        }
        
        public Script(byte[] buffer, int length, IEnumerable<string> stringTable, Function[] functionTable)
        {
            this.Buffer = new byte[length];
            System.Buffer.BlockCopy(buffer, 0, this.Buffer, 0, length);
            if (stringTable != null)
                this.stringTable = new List<string>(stringTable);
            else
                this.stringTable = new List<string>();
            this.readonlyStringTable = new ReadOnlyCollection<string>(this.stringTable);
            this.functionTable = functionTable;
        }
        #endregion
    }
}
