using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;
using Halak.Bibim.Scripting.Statements;

namespace Halak.Bibim.Scripting
{
    public class BinaryScriptGenerator
    {
        #region Fields
        #endregion

        #region Properties
        #endregion

        #region Constructors
        public BinaryScriptGenerator()
        {
        }
        #endregion

        #region Methods
        public void Generate(Stream output, Statement statement)
        {
            if (output == null)
                throw new ArgumentNullException("output");
            if (statement == null)
                throw new ArgumentNullException("statement");

            Context context = new Context(this, output);
            context.Write(statement);
        }
        #endregion

        #region Context (Nested Class)
        public class Context : BinaryWriter
        {
            #region Properties
            private Dictionary<Label, int> addresses;
            private Dictionary<Label, List<int>> reservedAddresses;
            #endregion

            #region Constructors
            public Context(BinaryScriptGenerator generator, Stream output)
                : base(output)
            {
                addresses = new Dictionary<Label, int>();
                reservedAddresses = new Dictionary<Label, List<int>>();
            }
            #endregion

            #region Methods
            public override void Close()
            {
                base.Close();
            }

            public void Write(ScriptCommandID value)
            {
                Write((byte)value);
            }

            public void Write(Statement value)
            {
                value.Generate(this);
            }

            public void WriteLabel(Label value)
            {
                Trace.Assert(addresses.ContainsKey(value) == false);

                int currentPosition = (int)BaseStream.Position;
                addresses.Add(value, currentPosition);

                List<int> positions = null;
                if (reservedAddresses.TryGetValue(value, out positions))
                {
                    foreach (int item in positions)
                    {
                        BaseStream.Position = item;
                        Write(currentPosition);
                    }

                    BaseStream.Position = (long)currentPosition;
                    reservedAddresses.Remove(value);
                }
            }

            public void WriteAddress(Label value)
            {
                int address = 0;
                if (addresses.TryGetValue(value, out address))
                    Write(address);
                else
                {
                    int currentPosition = (int)BaseStream.Position;
                    List<int> positions = null;
                    if (reservedAddresses.TryGetValue(value, out positions))
                        positions.Add(currentPosition);
                    else
                        reservedAddresses.Add(value, new List<int>() { currentPosition });

                    // 나중에 WriteLabel에서 덮어 씌울 것이기 때문에 공간은 할당해 놓습니다.
                    Write(address);
                }
            }

            public bool TryGetVariableOffsetFromStack(string name, out int stackIndex, out int localOffset)
            {
                if (name == "i")
                {
                    stackIndex = 0;
                    localOffset = 0;
                    return true;
                }
                else if (name == "result")
                {
                    stackIndex = 0;
                    localOffset = 4;
                    return true;
                }
                else
                {
                    stackIndex = -1;
                    localOffset = -1;
                    return false;
                }
            }
            #endregion
        }
        #endregion
    }
}
