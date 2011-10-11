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
        private readonly string[] stringTable;
        private readonly Function[] functionTable;
        #endregion

        #region Properties
        public byte[] Buffer
        {
            get;
            private set;
        }

        public string[] StringTable
        {
            get { return stringTable; }
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
        
        public Script(byte[] buffer, int length, string[] stringTable, Function[] functionTable)
        {
            this.Buffer = new byte[length];
            System.Buffer.BlockCopy(buffer, 0, this.Buffer, 0, length);
            this.stringTable = stringTable;
            this.functionTable = functionTable;
        }
        #endregion
    }
}
