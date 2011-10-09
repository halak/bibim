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
        public Script Generate(Statement statement)
        {
            MemoryStream memoryStream = new MemoryStream();

            if (statement == null)
                throw new ArgumentNullException("statement");

            Context context = new Context(this, memoryStream, statement as Block);
            context.Write(statement);
            context.FunctionTable.Sort((a, b) => string.Compare(a.Name, b.Name));

            return new Script(memoryStream.GetBuffer(), (int)memoryStream.Length, null, context.FunctionTable.ToArray());
        }
        #endregion

        #region Context (Nested Class)
        public class Context : BinaryWriter
        {
            #region Fields
            private Block block;
            private Dictionary<Label, int> addresses;
            private Dictionary<Label, List<int>> reservedAddresses;
            private List<DeclareVariable> localVariables;
            #endregion

            #region Properties
            public List<Script.Function> FunctionTable
            {
                get;
                private set;
            }
            #endregion

            #region Constructors
            public Context(BinaryScriptGenerator generator, Stream output, Block block)
                : base(output)
            {
                this.block = block;
                this.addresses = new Dictionary<Label, int>();
                this.reservedAddresses = new Dictionary<Label, List<int>>();
                this.localVariables = new List<DeclareVariable>();
                this.FunctionTable = new List<Script.Function>();
            }
            #endregion

            #region Methods
            public override void Close()
            {
                base.Close();
            }

            public Function FindFunction(string name)
            {
                return FindFunction(block, name);
            }

            private static Function FindFunction(Block block, string name)
            {
                foreach (Statement item in block.Statements)
                {
                    Block subBlock = item as Block;
                    if (subBlock != null)
                    {
                        Function function = subBlock as Function;
                        if (function != null)
                        {
                            if (function.Name == name)
                                return function;
                        }

                        Function foundFunction = FindFunction(subBlock, name);
                        if (foundFunction != null)
                            return foundFunction;
                    }
                }

                return null;
            }

            #region Write
            public void Write(ScriptCommandID value)
            {
                Write((byte)value);
            }

            public void Write(Statement value)
            {
                Function function = value as Function;
                if (function != null)
                {
                    int argumentStackSize = 0;
                    ScriptObjectType[] parameterTypes = new ScriptObjectType[function.Parameters.Count];
                    for (int i = 0; i < parameterTypes.Length; i++)
                    {
                        parameterTypes[i] = function.Parameters[i].Type;
                        argumentStackSize += DeclareVariable.SizeOf(parameterTypes[i]);
                    }

                    FunctionTable.Add(new Script.Function(function.Name, (int)BaseStream.Position, argumentStackSize, function.ReturnType, parameterTypes));
                }

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
            #endregion

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
