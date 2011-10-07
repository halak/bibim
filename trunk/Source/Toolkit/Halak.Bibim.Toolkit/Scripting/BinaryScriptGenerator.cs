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
            private Dictionary<Label, uint> addresses;
            private Dictionary<Label, List<uint>> reservedAddresses;
            #endregion

            #region Constructors
            public Context(BinaryScriptGenerator generator, Stream output)
                : base(output)
            {
                addresses = new Dictionary<Label, uint>();
                reservedAddresses = new Dictionary<Label, List<uint>>();
            }
            #endregion

            #region Methods
            public override void Close()
            {
                base.Close();
            }

            public void Write(ScriptProcess.CommandID value)
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

                uint currentPosition = (uint)BaseStream.Position;
                addresses.Add(value, currentPosition);

                List<uint> positions = null;
                if (reservedAddresses.TryGetValue(value, out positions))
                {
                    foreach (uint item in positions)
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
                uint address = 0;
                if (addresses.TryGetValue(value, out address))
                    Write(address);
                else
                {
                    uint currentPosition = (uint)BaseStream.Position;
                    List<uint> positions = null;
                    if (reservedAddresses.TryGetValue(value, out positions))
                        positions.Add(currentPosition);
                    else
                        reservedAddresses.Add(value, new List<uint>() { currentPosition });
                }
            }

            public int GetLocalVariableIndex(string name)
            {
                return -1;
            }
            #endregion
        }
        #endregion
    }
}
