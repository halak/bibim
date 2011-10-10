using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.IO;
using System.Text;
using Halak.Bibim.Scripting.Statements;

namespace Halak.Bibim.Scripting
{
    public class ScriptCompiler
    {
        #region Fields
        #endregion

        #region Properties
        #endregion

        #region Constructors
        public ScriptCompiler()
        {
        }
        #endregion

        #region Methods
        public Script Compile(Block codeBlock)
        {
            string text = string.Empty;
            return Compile(codeBlock, out text, false);
        }

        public Script Compile(Block codeBlock, out string textCode)
        {
            return Compile(codeBlock, out textCode, true);
        }

        private Script Compile(Block codeBlock, out string textCode, bool generateTextCode)
        {
            if (codeBlock == null)
                throw new ArgumentNullException("codeBlock");

            MemoryStream ms = new MemoryStream();
            Context context = new Context(this, ms, codeBlock, generateTextCode);
            context.Start();

            if (generateTextCode)
                textCode = context.TextCode;
            else
                textCode = string.Empty;

            Script.Function[] functions = new Script.Function[context.BriefFunctionTable.Count];
            context.BriefFunctionTable.CopyTo(functions, 0);

            return new Script(ms.GetBuffer(), (int)ms.Length, null, functions);
        }
        #endregion

        #region Context (Nested Class)
        public class Context
        {
            #region Fields
            private Writer binaryWriter;
            private StringBuilder textWriter;

            private List<Block> blockStack;
            private ReadOnlyCollection<Block> readOnlyBlockStack;

            private Dictionary<Label, int> labelAddresses;
            private Dictionary<Label, List<int>> reservedLabelAddresses;
            private Dictionary<Label, Guid> reservedLabelGuids;

            private List<Function> functionTable;
            private ReadOnlyCollection<Function> readOnlyFunctionTable;
            private List<Script.Function> briefFunctionTable;
            private ReadOnlyCollection<Script.Function> readOnlyBriefFunctionTable;

            private List<List<DeclareVariable>> virtualLocalVariableStack;
            #endregion

            #region Properties
            public IList<Block> CurrentBlocks
            {
                get { return readOnlyBlockStack; }
            }

            public Block CurrentBlock
            {
                get
                {
                    if (blockStack.Count > 0)
                        return blockStack[blockStack.Count - 1];
                    else
                        return null;
                }
            }

            public Function CurrentFunction
            {
                get
                {
                    for (int i = blockStack.Count - 1; i >= 0; i++)
                    {
                        if (blockStack[i] is Function)
                            return (Function)blockStack[i];
                    }

                    return null;
                }
            }

            public string TextCode
            {
                get
                {
                    if (textWriter != null)
                        return textWriter.ToString();
                    else
                        return null;
                }
            }

            public IList<Script.Function> BriefFunctionTable
            {
                get { return readOnlyBriefFunctionTable; }
            }

            private Block RootBlock
            {
                get
                {
                    if (blockStack.Count > 0)
                        return blockStack[0];
                    else
                        return null;
                }
            }
            #endregion

            #region Constructors
            public Context(ScriptCompiler compiler, Stream output, Block codeBlock, bool generateTextCode)
            {
                this.binaryWriter = new Writer(output);
                if (generateTextCode)
                    this.textWriter = new StringBuilder();
                else
                    this.textWriter = null;

                this.blockStack = new List<Block>() { codeBlock };
                this.readOnlyBlockStack = new ReadOnlyCollection<Block>(this.blockStack);

                this.labelAddresses = new Dictionary<Label, int>();
                this.reservedLabelAddresses = new Dictionary<Label, List<int>>();
                if (textWriter != null)
                    this.reservedLabelGuids = new Dictionary<Label, Guid>();
                else
                    this.reservedLabelGuids = null;

                this.functionTable = new List<Function>();
                this.readOnlyFunctionTable = new ReadOnlyCollection<Function>(this.functionTable);
                this.briefFunctionTable = new List<Script.Function>();
                this.readOnlyBriefFunctionTable = new ReadOnlyCollection<Script.Function>(this.briefFunctionTable);
            }
            #endregion

            #region Methods
            public void Start()
            {
                BuildFunctionTable(RootBlock);

                Generate(RootBlock);

                BuildBriefFunctionTable();
            }

            #region Generate
            public void Generate(Statement value)
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
                        for (int i = 0; i < ((Function)value).Parameters.Count; i++)
                        {
                            virtualLocalVariableStack.Add(new List<DeclareVariable>());
                            virtualLocalVariableStack[virtualLocalVariableStack.Count - 1].Add(((Function)value).Parameters[i]);
                        }
                        virtualLocalVariableStack.Add(new List<DeclareVariable>());
                        virtualLocalVariableStack.Add(new List<DeclareVariable>());

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
                        virtualLocalVariableStack.RemoveAt(virtualLocalVariableStack.Count - 1);
                        virtualLocalVariableStack.RemoveAt(virtualLocalVariableStack.Count - 1);
                        for (int i = 0; i < ((Function)value).Parameters.Count; i++)
                            virtualLocalVariableStack.RemoveAt(virtualLocalVariableStack.Count - 1);
                    }
                }

                Function = oldFunction;
            }

            #region Push & Pop
            #region Push Constant
            public void Push(bool value)
            {
                binaryWriter.Write(ScriptInstruction.Push1);
                binaryWriter.Write(value);

                if (textWriter != null)
                    textWriter.AppendLine(string.Format("push {0}\n", value.ToString()));

                PushVS();
            }

            public void Push(int value)
            {
                binaryWriter.Write(ScriptInstruction.Push4);
                binaryWriter.Write(value);

                if (textWriter != null)
                    textWriter.AppendLine(string.Format("push {0}\n", value.ToString()));

                PushVS();
            }

            public void Push(uint value)
            {
                binaryWriter.Write(ScriptInstruction.Push4);
                binaryWriter.Write(value);

                if (textWriter != null)
                    textWriter.AppendLine(string.Format("push {0}U\n", value.ToString()));

                PushVS();
            }

            public void Push(long value)
            {
                binaryWriter.Write(ScriptInstruction.Push8);
                binaryWriter.Write(value);

                if (textWriter != null)
                    textWriter.AppendLine(string.Format("push {0}L\n", value.ToString()));

                PushVS();
            }

            public void Push(float value)
            {
                binaryWriter.Write(ScriptInstruction.Push4);
                binaryWriter.Write(value);

                if (textWriter != null)
                    textWriter.AppendLine(string.Format("push {0}f\n", value.ToString()));

                PushVS();
            }

            public void Push(byte[] value)
            {
                switch (value.Length)
                {
                    case 1:
                        binaryWriter.Write(ScriptInstruction.Push1);
                        break;
                    case 4:
                        binaryWriter.Write(ScriptInstruction.Push4);
                        break;
                    case 8:
                        binaryWriter.Write(ScriptInstruction.Push8);
                        break;
                    case 12:
                        binaryWriter.Write(ScriptInstruction.Push12);
                        break;
                    case 16:
                        binaryWriter.Write(ScriptInstruction.Push16);
                        break;
                    default:
                        binaryWriter.Write(ScriptInstruction.PushN);
                        binaryWriter.Write(value.Length);
                        break;
                }

                binaryWriter.Write(value);

                if (textWriter != null)
                    textWriter.AppendLine(string.Format("push({0}) {{ {1} }}\n", value.Length, string.Join(",", (IEnumerable<byte>)value)));

                PushVS();
            }
            #endregion

            #region Push Variable
            public void PushVariable(string name)
            {
                int stackIndex;
                int localOffset;
                int size;
                if (TryGetVariableOffsetFromStack(name, out stackIndex, out localOffset, out size))
                {
                    binaryWriter.Write(ScriptInstruction.PushLocalVariable);
                    binaryWriter.Write(stackIndex);
                    binaryWriter.Write(localOffset);
                    binaryWriter.Write(size);

                    if (textWriter != null)
                        textWriter.AppendLine(string.Format("pushv {0}, {1}, {2} [{3}]", stackIndex, localOffset, size, name));
                }
                else
                {
                    throw new NotImplementedException();
                }

                PushVS();
            }
            #endregion

            #region Push Allocate-only
            public void AllocateN(int size)
            {
                if (size < 0)
                    throw new ArgumentException("count");

                binaryWriter.Write(ScriptInstruction.AllocateN);
                binaryWriter.Write(size);

                if (textWriter != null)
                    textWriter.AppendLine(string.Format("push({0})", size));

                PushVS();
            }
            #endregion

            #region Pop
            public void Pop(int count)
            {
                if (count < 0)
                    throw new ArgumentException("count");

                switch (count)
                {
                    case 1:
                        binaryWriter.Write(ScriptInstruction.Pop1);
                        break;
                    case 2:
                        binaryWriter.Write(ScriptInstruction.Pop2);
                        break;
                    case 4:
                        binaryWriter.Write(ScriptInstruction.Pop3);
                        break;
                    case 12:
                        binaryWriter.Write(ScriptInstruction.Pop4);
                        break;
                    default:
                        binaryWriter.Write(ScriptInstruction.PopN);
                        binaryWriter.Write(count);
                        break;
                }

                if (textWriter != null)
                    textWriter.AppendLine(string.Format("pop {0}", count));

                PopVS(count);
            }
            #endregion
            #endregion

            #region Jump
            public void Jump(Label destination)
            {
                binaryWriter.Write(ScriptInstruction.Jump);
                string addressString = WriteAddress(destination);

                if (textWriter != null)
                {
                    if (string.IsNullOrEmpty(destination.Name))
                        textWriter.AppendLine(string.Format("jump {0}", addressString));
                    else
                        textWriter.AppendLine(string.Format("jump {0} [{1}]", addressString, destination.Name));
                }
            }

            public void IfFalseThenJump(Expression condition, Label destination)
            {
                Generate(condition);
                binaryWriter.Write(ScriptInstruction.IfFalseThenJump);
                string addressString = WriteAddress(destination);

                if (string.IsNullOrEmpty(destination.Name))
                    textWriter.AppendLine(string.Format("if_jump {0}", addressString));
                else
                    textWriter.AppendLine(string.Format("if_jump {0} [{1}]", addressString, destination.Name));

                PopVS(1);
            }

            public void Return(Expression value)
            {
                LocalAssign(CurrentFunction.Parameters.Count - 5, 0, value, "return @1");
                binaryWriter.Write(ScriptInstruction.Return);
            }
            #endregion

            #region Assign
            public void Assign(string variableName, Expression value)
            {
                int stackIndex;
                int localOffset;
                int size;
                if (TryGetVariableOffsetFromStack(variableName, out stackIndex, out localOffset, out size))
                    LocalAssign(stackIndex, localOffset, value, variableName);
                else
                    throw new NotImplementedException();

                PopVS(1);
            }

            private void LocalAssign(int stackIndex, int localOffset, Expression value, string variableName)
            {
                Generate(value);
                binaryWriter.Write(ScriptInstruction.LocalAssign);
                binaryWriter.Write(stackIndex);
                binaryWriter.Write(localOffset);

                if (textWriter != null)
                {
                    if (string.IsNullOrEmpty(variableName))
                        textWriter.AppendLine(string.Format("assign {0}, {1}", stackIndex, localOffset));
                    else
                        textWriter.AppendLine(string.Format("assign {0}, {1} [{3}]", stackIndex, localOffset, variableName));
                }
            }
            #endregion

            #region Operators
            public void BinaryOperator(ScriptInstruction instruction, Expression leftOperand, Expression rightOperand)
            {
                Generate(leftOperand);
                Generate(rightOperand);
                binaryWriter.Write(instruction);

                if (textWriter != null)
                {
                    string instructionString = string.Empty;
                    switch (instruction)
                    {
                        case ScriptInstruction.AddInt:
                            instructionString = "addI";
                            break;
                        case ScriptInstruction.SubtractInt:
                            instructionString = "subI";
                            break;
                        case ScriptInstruction.MultiplyInt:
                            instructionString = "mulI";
                            break;
                        case ScriptInstruction.TestEqualityInt:
                            instructionString = "_eqI";
                            break;
                        case ScriptInstruction.TestInequalityInt:
                            instructionString = "inqI";
                            break;
                        default:
                            throw new NotSupportedException(string.Format("{0} is not binary operator.", instruction.ToString()));
                    }

                    textWriter.AppendLine(string.Format("{0}", instructionString));
                }

                PopVS(2);
                PushVS();
            }
            #endregion
            #endregion

            #region Function-table Manipulation
            public Function FindFunction(string name)
            {
                return functionTable.Find((item) => { return item.Name == name; });
            }

            private void BuildFunctionTable(Block block)
            {
                IList<Statement> functionStatements = block.FindAll((item) => { return item is Function; });
                foreach (Statement item in functionStatements)
                    functionTable.Add((Function)item);
            }

            private void BuildBriefFunctionTable()
            {
                briefFunctionTable.Clear();
                foreach (Function item in functionTable)
                {
                    ScriptObjectType[] rt = new ScriptObjectType[item.ReturnTypes.Count];
                    ScriptObjectType[] pt = new ScriptObjectType[item.Parameters.Count];

                    for (int i = 0; i < rt.Length; i++)
                        rt[i] = item.ReturnTypes[i];
                    for (int i = 0; i < rt.Length; i++)
                        pt[i] = item.Parameters[i].Type;

                    briefFunctionTable.Add(new Script.Function(item.Name, labelAddresses[item.BeginLabel], 0, rt, pt));
                }
                briefFunctionTable.Sort((a, b) => { return string.Compare(a.Name, b.Name); });
            }
            #endregion

            #region Virtual-stack Manipulation
            private void PushVS()
            {
                virtualLocalVariableStack.Add(new List<DeclareVariable>());
            }

            private void PopVS(int count)
            {
                for (int i = 0; i < count; i++)
                    virtualLocalVariableStack.RemoveAt(virtualLocalVariableStack.Count - 1);
            }
            #endregion

            #region Label addressing
            public void InidicateLabel(Label value)
            {
                Trace.Assert(labelAddresses.ContainsKey(value) == false);

                int currentPosition = (int)binaryWriter.BaseStream.Position;
                labelAddresses.Add(value, currentPosition);

                List<int> positions = null;
                if (reservedLabelAddresses.TryGetValue(value, out positions))
                {
                    foreach (int item in positions)
                    {
                        binaryWriter.BaseStream.Position = item;
                        binaryWriter.Write(currentPosition);
                    }

                    binaryWriter.BaseStream.Position = (long)currentPosition;
                    reservedLabelAddresses.Remove(value);
                }

                Guid guid = Guid.Empty;
                if (reservedLabelGuids != null && reservedLabelGuids.TryGetValue(value, out guid))
                {
                    textWriter.Replace(guid.ToString(), currentPosition.ToString());
                    reservedLabelGuids.Remove(value);
                }

                if (textWriter != null)
                    textWriter.AppendLine(string.Format("[label] {0}:", value.Name));
            }

            public string WriteAddress(Label value)
            {
                int address = 0;
                if (labelAddresses.TryGetValue(value, out address))
                {
                    binaryWriter.Write(address);
                    return address.ToString();
                }
                else
                {
                    int currentPosition = (int)binaryWriter.BaseStream.Position;
                    List<int> positions = null;
                    if (reservedLabelAddresses.TryGetValue(value, out positions))
                        positions.Add(currentPosition);
                    else
                        reservedLabelAddresses.Add(value, new List<int>() { currentPosition });

                    // 나중에 WriteLabel에서 덮어 씌울 것이기 때문에 공간은 할당해 놓습니다.
                    binaryWriter.Write(address);

                    if (reservedLabelGuids != null)
                    {
                        Guid guid = Guid.NewGuid();
                        reservedLabelGuids.Add(value, guid);
                        return guid.ToString();
                    }
                    else
                        return string.Empty;
                }
            }

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
            #endregion

            #region Writer (Nested Class)
            private sealed class Writer : BinaryWriter
            {
                public Writer(Stream output)
                    : base(output)
                {
                }

                public void Write(ScriptInstruction instruction)
                {
                    base.Write((byte)instruction);
                }
            }
            #endregion
        }
        #endregion
    }
}
