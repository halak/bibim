using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.IO;
using System.Text;
using Halak.Bibim.Reflection;
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

            string[] strings = new string[context.StringTable.Count];
            context.StringTable.CopyTo(strings, 0);

            return new Script(ms.GetBuffer(), (int)ms.Length, strings, functions);
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

            private List<string> stringTable;
            private ReadOnlyCollection<string> readOnlyStringTable;

            private List<List<DeclareVariable>> localVariableVirtualStack;
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
                    for (int i = blockStack.Count - 1; i >= 0; i--)
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

            public IList<string> StringTable
            {
                get { return stringTable; }
            }

            private Block RootBlock
            {
                get;
                set;
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

                this.blockStack = new List<Block>();
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

                this.stringTable = new List<string>();
                this.readOnlyStringTable = new ReadOnlyCollection<string>(this.stringTable);

                this.localVariableVirtualStack = new List<List<DeclareVariable>>();

                this.RootBlock = codeBlock;
            }
            #endregion

            #region Methods
            public void Start()
            {
                BuildFunctionTable(RootBlock);

                foreach (Statement item in RootBlock.Statements)
                    Generate(item);

                BuildBriefFunctionTable();
            }

            #region Generate
            public void Generate(Statement value)
            {
                bool isDeclareVariable = value is DeclareVariable;
                bool isBlock = (isDeclareVariable == false) && (value is Block);
                bool isFunction = (isBlock) && (value is Function);
                if (isDeclareVariable)
                    GetVSTopLayer().Add((DeclareVariable)value);

                if (isBlock)
                {
                    if (isFunction)
                        BeginFunction((Function)value);

                    BeginBlock((Block)value);
                }

                value.Generate(this);

                if (isBlock)
                {
                    EndBlock((Block)value);

                    if (isFunction)
                        EndFunction((Function)value);
                }
            }

            #region Push & Pop
            #region Push Constant
            public void Push(bool value)
            {
                binaryWriter.Write(ScriptInstruction.Push1);
                binaryWriter.Write(value);

                if (textWriter != null)
                    textWriter.AppendLine(string.Format("push {0}", value.ToString()));

                PushVS();
            }

            public void Push(int value)
            {
                binaryWriter.Write(ScriptInstruction.Push4);
                binaryWriter.Write(value);

                if (textWriter != null)
                    textWriter.AppendLine(string.Format("push {0}", value.ToString()));

                PushVS();
            }

            public void Push(uint value)
            {
                binaryWriter.Write(ScriptInstruction.Push4);
                binaryWriter.Write(value);

                if (textWriter != null)
                    textWriter.AppendLine(string.Format("push {0}U", value.ToString()));

                PushVS();
            }

            public void Push(long value)
            {
                binaryWriter.Write(ScriptInstruction.Push8);
                binaryWriter.Write(value);

                if (textWriter != null)
                    textWriter.AppendLine(string.Format("push {0}L", value.ToString()));

                PushVS();
            }

            public void Push(float value)
            {
                binaryWriter.Write(ScriptInstruction.Push4);
                binaryWriter.Write(value);

                if (textWriter != null)
                    textWriter.AppendLine(string.Format("push {0}f", value.ToString()));

                PushVS();
            }

            public void Push(string value)
            {
                int index = stringTable.IndexOf(value);
                if (index == -1)
                {
                    stringTable.Add(value);
                    index = stringTable.Count - 1;
                }

                binaryWriter.Write(ScriptInstruction.Push4);
                binaryWriter.Write(index);

                if (textWriter != null)
                    textWriter.AppendLine(string.Format("push {0}S >> \"{1}\"", index, value));

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
                    textWriter.AppendLine(string.Format("push({0}) {{ {1} }}", value.Length, string.Join(",", (IEnumerable<byte>)value)));

                PushVS();
            }
            #endregion

            #region Push Variable
            public void PushVariable(string name)
            {
                int stackIndex;
                int localOffset;
                int size;
                if (TryGetVariableOffsetFromVS(name, out stackIndex, out localOffset, out size))
                {
                    binaryWriter.Write(ScriptInstruction.PushLocalVariable);
                    binaryWriter.Write(stackIndex);
                    binaryWriter.Write(localOffset);
                    binaryWriter.Write(size);

                    if (textWriter != null)
                        textWriter.AppendLine(string.Format("pushv ({0}, {1}, {2}) [{3}]", stackIndex, localOffset, size, name));
                }
                else
                {
                    throw new NotImplementedException();
                }

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
                Generate(value);
                LocalAssign((-1) + (-1) + (-1) + (-1) + (-CurrentFunction.Parameters.Count) + (-1), 0, "return @1");
                binaryWriter.Write(ScriptInstruction.Return);

                if (textWriter != null)
                    textWriter.AppendLine(string.Format("ret"));
            }
            #endregion

            #region Function
            public void Function(int stackSize)
            {
                // BeginFunction에서 이미 이 할당에 대한 Virtual-stack 구축을 끝마쳤기 때문에 PushVS를 하지 않습니다.
                AllocateN(stackSize, false);
            }

            public void CallScriptFunction(string name, Expression[] args)
            {
                Function function = FindFunction(name);
                if (function == null)
                    throw new InvalidOperationException("Function not found");
                
                // return value들을 보관할 영역을 확보합니다.
                foreach (ScriptObjectType item in function.ReturnTypes)
                    AllocateN(DeclareVariable.SizeOf(item), true);

                for (int i = 0; i < args.Length; i++)
                    Generate(args[i]);

                binaryWriter.Write(ScriptInstruction.CallScriptFunction);
                string addressString = WriteAddress(function.BeginLabel);
                binaryWriter.Write(args.Length);

                if (textWriter != null)
                    textWriter.AppendLine(string.Format("call {0} [{1}]", addressString, name));

                // 실행에서 Pop은 return에서 해주므로 여기서는 VS에서만 Pop해줍니다.
                PopVS(args.Length);
            }

            public void CallNativeFunction(string name, Expression[] args)
            {
                ScriptNativeFunction function = ScriptNativeFunctionTable.Find(name);
                if (function == null)
                    throw new InvalidOperationException("Function not found");

                ScriptNativeFunctionAttribute functionAttribute = function.Method.GetCustomAttribute<ScriptNativeFunctionAttribute>();
                ScriptNativeFunctionReturnAttribute[] returnTypes = function.Method.GetCustomAttributes<ScriptNativeFunctionReturnAttribute>();
                ScriptNativeFunctionParameterAttribute[] parameterTypes = function.Method.GetCustomAttributes<ScriptNativeFunctionParameterAttribute>();

                // return value들을 보관할 영역을 확보합니다.
                foreach (ScriptNativeFunctionReturnAttribute item in returnTypes)
                    AllocateN(DeclareVariable.SizeOf(item.Type), true);

                Trace.Assert(parameterTypes.Length == args.Length);
                for (int i = 0; i < args.Length; i++)
                    Generate(args[i]);

                binaryWriter.Write(ScriptInstruction.CallNativeFunction);
                binaryWriter.Write(functionAttribute.FunctionID);
                binaryWriter.Write(returnTypes.Length);
                binaryWriter.Write(parameterTypes.Length);

                if (textWriter != null)
                    textWriter.AppendLine(string.Format("call_native {0} [{1}]", functionAttribute.FunctionID, name));

                Pop(parameterTypes.Length);
            }

            private void AllocateN(int size, bool pushVS)
            {
                if (size < 0)
                    throw new ArgumentException("count");

                binaryWriter.Write(ScriptInstruction.AllocateN);
                binaryWriter.Write(size);

                if (textWriter != null)
                    textWriter.AppendLine(string.Format("push({0})", size));

                if (pushVS)
                    PushVS();
            }
            #endregion

            #region Operators
            public void Assign(string variableName, Expression value)
            {
                Generate(value);

                int stackIndex;
                int localOffset;
                int size;
                if (TryGetVariableOffsetFromVS(variableName, out stackIndex, out localOffset, out size))
                    LocalAssign(stackIndex, localOffset, variableName);
                else
                    throw new NotImplementedException();
            }

            private void LocalAssign(int stackIndex, int localOffset, string variableName)
            {
                binaryWriter.Write(ScriptInstruction.LocalAssign);
                binaryWriter.Write(stackIndex);
                binaryWriter.Write(localOffset);

                if (textWriter != null)
                {
                    if (string.IsNullOrEmpty(variableName))
                        textWriter.AppendLine(string.Format("move ({0}, {1})", stackIndex, localOffset));
                    else
                        textWriter.AppendLine(string.Format("move ({0}, {1}) [{2}]", stackIndex, localOffset, variableName));
                }

                PopVS(1);
            }

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
                    for (int i = 0; i < pt.Length; i++)
                        pt[i] = item.Parameters[i].Type;

                    briefFunctionTable.Add(new Script.Function(item.Name, labelAddresses[item.BeginLabel], 0, rt, pt));
                }
                briefFunctionTable.Sort((a, b) => { return string.Compare(a.Name, b.Name); });
            }
            #endregion

            #region Virtual-stack Manipulation
            private void PushVS()
            {
                localVariableVirtualStack.Add(null);
            }

            private void PopVS(int count)
            {
                List<List<DeclareVariable>> lvvs = localVariableVirtualStack;

                Trace.Assert(count <= lvvs.Count);
                for (int i = 0; i < count; i++)
                    lvvs.RemoveAt(lvvs.Count - 1);
            }

            public bool TryGetVariableOffsetFromVS(string name, out int stackIndex, out int localOffset, out int size)
            {
                List<List<DeclareVariable>> lvvs = localVariableVirtualStack;

                stackIndex = -1;
                localOffset = 0;
                size = 0;
                for (int i = lvvs.Count - 1; i >= 0; i--, stackIndex--)
                {
                    List<DeclareVariable> items = lvvs[i];
                    if (items == null)
                        continue;

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

            #region Block & Function
            public void BeginBlock(Block block)
            {
                blockStack.Add(block);
            }

            public void EndBlock(Block block)
            {
                List<DeclareVariable> declarations = GetVSTopLayer();
                foreach (DeclareVariable item in block.GetVariableDeclarations(false))
                {
                    bool result = declarations.Remove(item);
                    Trace.Assert(result);
                }

                blockStack.RemoveAt(blockStack.Count - 1);
            }

            private void BeginFunction(Function function)
            {
                // Stack layout in Function call (Top-down)
                // ==============================
                // 1st Return value space
                // ------------------------------
                // 2nd Return value space
                // ------------------------------
                // ...
                // ------------------------------
                // N Return value space
                // ==============================
                // 1st Argument
                // ------------------------------
                // 2nd Argument
                // ------------------------------
                // ...
                // ------------------------------
                // N Argument
                // ==============================
                // Caller-address
                // ==============================
                // Number of arugments
                // ==============================
                // 1st Local variable
                // 2nd Local variable
                // ...
                // N Local variable
                // ==============================

                for (int i = 0; i < function.ReturnTypes.Count; i++)
                    PushVS();
                
                for (int i = 0; i < function.Parameters.Count; i++)
                {
                    PushVS();
                    GetVSTopLayer().Add(function.Parameters[i]);
                }

                PushVS(); // Caller-address
                PushVS(); // Number of arugments
                PushVS(); // Local-variables
            }

            private void EndFunction(Function function)
            {
                PopVS(1 + 1 + 1 + function.Parameters.Count + function.ReturnTypes.Count);
            }

            private List<DeclareVariable> GetVSTopLayer()
            {
                List<List<DeclareVariable>> lvvs = localVariableVirtualStack;

                lvvs[lvvs.Count - 1] = lvvs[lvvs.Count - 1] ?? new List<DeclareVariable>();
                return lvvs[lvvs.Count - 1];
            }
            #endregion
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
                    textWriter.AppendLine(string.Format("[label] {0} => {1}:", currentPosition, value.Name));
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
