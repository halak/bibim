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
            private List<List<DeclareVariable>> virtualLocalVariableStack;
            #endregion

            #region Properties
            public Function Function
            {
                get;
                private set;
            }

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
                this.virtualLocalVariableStack = new List<List<DeclareVariable>>();
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

            public void GeneratePushValue(byte[] value)
            {
                switch (value.Length)
                {
                    case 1:
                        Write(ScriptInstruction.Push1);
                        break;
                    case 4:
                        Write(ScriptInstruction.Push4);
                        break;
                    case 8:
                        Write(ScriptInstruction.Push8);
                        break;
                    case 12:
                        Write(ScriptInstruction.Push12);
                        break;
                    case 16:
                        Write(ScriptInstruction.Push16);
                        break;
                    default:
                        Write(ScriptInstruction.PushN);
                        Write(value.Length);
                        break;
                }

                Write(value);

                virtualLocalVariableStack.Add(new List<DeclareVariable>());
            }

            public void GeneratePushVariable(string name)
            {
                int stackIndex;
                int localOffset;
                int size;
                if (TryGetVariableOffsetFromStack(name, out stackIndex, out localOffset, out size))
                {
                    Write(ScriptInstruction.PushLocalVariable);
                    Write(stackIndex);
                    Write(localOffset);
                    Write(size);
                }
                else
                {
                    Write(ScriptInstruction.PushGlobalVariable);
                    Write(name);
                }

                virtualLocalVariableStack.Add(new List<DeclareVariable>());
            }

            public void GenerateAllocateN(int size)
            {
                Write(ScriptInstruction.AllocateN);
                Write(size);
            }

            public void GeneratePop(int count)
            {
                switch (count)
                {
                    case 1:
                        Write(ScriptInstruction.Pop1);
                        break;
                    case 2:
                        Write(ScriptInstruction.Pop2);
                        break;
                    case 4:
                        Write(ScriptInstruction.Pop3);
                        break;
                    case 12:
                        Write(ScriptInstruction.Pop4);
                        break;
                    default:
                        Write(ScriptInstruction.PopN);
                        Write(count);
                        break;
                }

                //virtualLocalVariableStack.RemoveAt(virtualLocalVariableStack.Count - 1);
            }

            public void GenerateJump(Label destination)
            {
                Write(ScriptInstruction.Jump);
                WriteAddress(destination);
            }

            public void GenerateIfFalseThenJump(Expression condition, Label destination)
            {
                Write(condition);
                Write(ScriptInstruction.IfFalseThenJump);
                WriteAddress(destination);

                virtualLocalVariableStack.RemoveAt(virtualLocalVariableStack.Count - 1);
            }

            public void GenerateReturn()
            {
                Write(ScriptInstruction.Return);
            }
            
            public void GenerateLocalAssign(string name, Expression value)
            {
            }

            public void GenerateLocalAssign(int stackIndex, int localOffset)
            {
                Write(ScriptInstruction.LocalAssign);
                Write(stackIndex);
                Write(localOffset);

                virtualLocalVariableStack.RemoveAt(virtualLocalVariableStack.Count - 1);
            }

            public void GenerateBinaryOperator(ScriptInstruction instruction, Expression leftOperand, Expression rightOperand)
            {
                Write(leftOperand);
                Write(rightOperand);
                Write(instruction);

                virtualLocalVariableStack.RemoveAt(virtualLocalVariableStack.Count - 1);
            }

            #region Write
            public void Write(ScriptInstruction value)
            {
                Write((byte)value);
            }

            public void Write(Statement value)
            {
                Function oldFunction = Function;
                Function function = value as Function;
                if (function != null)
                {
                    int argumentStackSize = 0;
                    ScriptObjectType[] parameterTypes = new ScriptObjectType[function.Parameters.Count];
                    ScriptObjectType[] returnTypes = new ScriptObjectType[1];
                    for (int i = 0; i < parameterTypes.Length; i++)
                    {
                        parameterTypes[i] = function.Parameters[i].Type;
                        argumentStackSize += DeclareVariable.SizeOf(parameterTypes[i]);
                    }
                    for (int i = 0; i < returnTypes.Length; i++)
                        returnTypes[i] = function.ReturnTypes[i];

                    Function = function;
                    FunctionTable.Add(new Script.Function(function.Name, (int)BaseStream.Position, argumentStackSize, returnTypes, parameterTypes));
                }

                if (value is Block)
                {
                    if (value is Function)
                    {
                        virtualLocalVariableStack.Add(new List<DeclareVariable>());
                    }

                    foreach (Statement item in ((Block)value).Statements)
                    {
                        if (item is DeclareVariable)
                            virtualLocalVariableStack[virtualLocalVariableStack.Count - 1].Add((DeclareVariable)item);
                    }
                }

                value.Generate(this);

                if (value is Block)
                {
                    foreach (Statement item in ((Block)value).Statements)
                    {
                        if (item is DeclareVariable)
                            virtualLocalVariableStack[virtualLocalVariableStack.Count - 1].Remove((DeclareVariable)item);

                    }
                    if (value is Function)
                    {
                        virtualLocalVariableStack.RemoveAt(virtualLocalVariableStack.Count - 1);
                    }
                }

                Function = oldFunction;
            }

            public void DeclareLabel(Label value)
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

            public bool TryGetVariableOffsetFromStack(string name, out int stackIndex, out int localOffset, out int size)
            {
                stackIndex = -1;
                localOffset = 0;
                size = 0;
                for (int i = virtualLocalVariableStack.Count - 1; i >= 0; i--, stackIndex--)
                {
                    List<DeclareVariable> items = virtualLocalVariableStack[i];
                    int k = items.Count - 1;
                    bool found = false;
                    for (k = items.Count - 1; k >= 0; k--)
                    {
                        DeclareVariable item = items[k];
                        if (item.Name == name)
                        {
                            size = DeclareVariable.SizeOf(item.Type);
                            found = true;
                            break;
                        }
                    }

                    for (k = k - 1; k >= 0; k--)
                        localOffset += DeclareVariable.SizeOf(items[k].Type);

                    if (found)
                        return true;
                }   

                return false;
            }
            #endregion
        }
        #endregion
    }
}
