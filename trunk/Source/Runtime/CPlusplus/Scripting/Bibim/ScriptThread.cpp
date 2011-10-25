#include <Bibim/PCH.h>
#include <Bibim/ScriptThread.h>
#include <Bibim/BinaryReader.h>
#include <Bibim/BinaryWriter.h>
#include <Bibim/Memory.h>
#include <Bibim/MemoryStream.h>
#include <Bibim/Script.h>
#include <Bibim/SCriptingContext.h>
#include <Bibim/ScriptNativeFunctionTable.h>

namespace Bibim
{
    enum ScriptInstruction
    {
        NOP,

        Push1,
        Push4,
        Push8,
        Push12,
        Push16,
        PushN,
        PushLocalVariable,
        PushGlobalVariable,
        AllocateN,
        Pop1,
        Pop2,
        Pop3,
        Pop4,
        PopN,

        Jump,
        IfFalseThenJump,
        CallScriptFunction,
        CallNativeFunction,
        Return,
        Yield,

        LocalAssign,
        GlobalAssign,
        AddInt,
        AddUInt,
        AddLongInt,
        AddFloat,
        AddInt2,
        AddInt3,
        AddInt4,
        AddFloat2,
        AddFloat3,
        AddFloat4,
        SubtractInt,
        SubtractUInt,
        SubtractLongInt,
        SubtractFloat,
        SubtractInt2,
        SubtractInt3,
        SubtractInt4,
        SubtractFloat2,
        SubtractFloat3,
        SubtractFloat4,
        MultiplyInt,
        TestEqualityInt,
        TestInequalityInt,

                    //ConcatenationOperator
                    //AssignmentOperator = 9,
                    //NegationOperator = 10,
                    //AdditionOperator = 11,
                    //SubtractionCommand = 12,
                    //MultiplicationOperator = 13,
                    //DivisionOperator = 14,
                    //ModulusOperator = 15,
                    //SquareBracketsOperator = 17,
                    //LogicalANDOperator = 16,
                    //LogicalOROperator = 17,
                    //LogicalXOROperator = 18,
                    //LogicalLeftShiftOperator = 19,
                    //LogicalRightShiftOperator = 20,
                    //LogicalNegation = 21,
                    //EqualityOperator = 21,
                    //InequalityOperator = 22,
                    //LessThanOperator = 23,
                    //GreaterThanOperator = 24,
                    //LessThanOrEqualOperator = 25,
                    //GreaterThanOrEqualOperator = 26,
                    //ConditionalANDOperator = 27,
                    //ConditionalOROperator = 28,
                    //AdditionAssignmentOperator = 29,
                    //SubtractionAssignmentOperator = 30,
                    //MultiplicationAssignmentOperator = 31,
                    //DivisionAssignmentOperator = 32,
                    //ModulusAssignmentOperator = 33,
                    //LogicalANDAssignmentOperator = 34,
                    //LogicalORAssignmentOperator = 35,
                    //LogicalXORAssignmentOperator = 36,
                    //LogicalLeftShiftAssignmentOperator = 37,
                    //LogicalRightShiftAssignmentOperator = 38,
    };

    ScriptThread::ScriptThread(Script* script)
        : script(script),
          stream(MemoryStream::NewReadableStream(&script->GetBuffer()[0], script->GetBuffer().size())),
          state(Stopped),
          nativeFunctionDepth(0),
          suspendedFunction(nullptr),
          suspendedTopIndex(-1)
    {
    }

    ScriptThread::ScriptThread(Script* script, int stackSize)
        : script(script),
          stack(stackSize),
          stream(MemoryStream::NewReadableStream(&script->GetBuffer()[0], script->GetBuffer().size())),
          state(Stopped),
          nativeFunctionDepth(0),
          suspendedFunction(nullptr),
          suspendedTopIndex(-1)
    {
    }

    ScriptThread::~ScriptThread()
    {
    }

    ScriptObject ScriptThread::Call(const String& name)
    {
        if (const Script::Function* function = BeginCall(name, 0))
            return EndCall(function);
        else
            return ScriptObject::Void;
    }

    ScriptObject ScriptThread::Call(const String& name, const ScriptObject& arg1)
    {
        if (const Script::Function* function = BeginCall(name, 1))
        {
            PushArgument(function->ParameterTypes[0], arg1);
            return EndCall(function);
        }
        else
            return ScriptObject::Void;
    }

    ScriptObject ScriptThread::Call(const String& name, const ScriptObject& arg1, const ScriptObject& arg2)
    {
        if (const Script::Function* function = BeginCall(name, 2))
        {
            PushArgument(function->ParameterTypes[0], arg1);
            PushArgument(function->ParameterTypes[1], arg2);
            return EndCall(function);
        }
        else
            return ScriptObject::Void;
    }

    ScriptObject ScriptThread::Call(const String& name, const ScriptObject& arg1, const ScriptObject& arg2, const ScriptObject& arg3)
    {
        if (const Script::Function* function = BeginCall(name, 3))
        {
            PushArgument(function->ParameterTypes[0], arg1);
            PushArgument(function->ParameterTypes[1], arg2);
            PushArgument(function->ParameterTypes[2], arg3);
            return EndCall(function);
        }
        else
            return ScriptObject::Void;
    }

    ScriptObject ScriptThread::Call(const String& name, const ScriptObject& arg1, const ScriptObject& arg2, const ScriptObject& arg3, const ScriptObject& arg4)
    {
        if (const Script::Function* function = BeginCall(name, 4))
        {
            PushArgument(function->ParameterTypes[0], arg1);
            PushArgument(function->ParameterTypes[1], arg2);
            PushArgument(function->ParameterTypes[2], arg3);
            PushArgument(function->ParameterTypes[3], arg4);
            return EndCall(function);
        }
        else
            return ScriptObject::Void;
    }

    ScriptObject ScriptThread::Call(const String& name, const ScriptObject& arg1, const ScriptObject& arg2, const ScriptObject& arg3, const ScriptObject& arg4, const ScriptObject& arg5)
    {
        if (const Script::Function* function = BeginCall(name, 5))
        {
            PushArgument(function->ParameterTypes[0], arg1);
            PushArgument(function->ParameterTypes[1], arg2);
            PushArgument(function->ParameterTypes[2], arg3);
            PushArgument(function->ParameterTypes[3], arg4);
            PushArgument(function->ParameterTypes[4], arg5);
            return EndCall(function);
        }
        else
            return ScriptObject::Void;
    }

    ScriptObject ScriptThread::Resume()
    {
        BBAssert(state == Suspended);
        state = Running;
        const Script::Function* temporarySuspendedFunction = nullptr;
        int temporarySuspendedTopIndex = -1;
        std::swap(temporarySuspendedFunction, suspendedFunction);
        std::swap(temporarySuspendedTopIndex, suspendedTopIndex);
        return Run(temporarySuspendedFunction, temporarySuspendedTopIndex);
    }

    const ScriptObject& ScriptThread::GetGlobal(uint id) const
    {
        std::map<uint, ScriptObject>::const_iterator it = globalVariables.find(id);
        if (it != globalVariables.end())
            return (*it).second;
        else
            return ScriptObject::Void;
    }

    void ScriptThread::SetGlobal(uint id, const ScriptObject& value)
    {
        if (value != ScriptObject::Void)
            globalVariables[id] = value;
        else
        {
            std::map<uint, ScriptObject>::iterator it = globalVariables.find(id);
            if (it != globalVariables.end())
                globalVariables.erase(it);
        }
    }

    const Script::Function* ScriptThread::BeginCall(const String& name, int numberOfArguments)
    {
        if (state == Suspended)
            return nullptr;

        if (const Script::Function* function = script->Find(name))
        {
            state = Running;

            // Return value를 보관할 영역을 확보합니다.
            const int count = static_cast<int>(function->ReturnTypes.size());
            for (int i = 0; i < count; i++)
                stack.Push(ScriptObject::SizeOf(function->ReturnTypes[i]));

            BBAssert(static_cast<int>(function->ParameterTypes.size()) == numberOfArguments);

            return function;
        }
        else
            return nullptr;
    }

    ScriptObject ScriptThread::EndCall(const Script::Function* function)
    {
        BBAssertDebug(function);

        stream->Seek(function->Position, Stream::FromBegin);

        int topIndex = stack.GetTopIndex();

        BinaryWriter::From(stack.Push(sizeof(int)), stream->GetPosition());
        BinaryWriter::From(stack.Push(sizeof(int)), function->ParameterTypes.size());

        return Run(function, topIndex);
    }

    void ScriptThread::PushArgument(ScriptObjectType type, const ScriptObject& value)
    {
        ScriptObject::WriteToBytes(stack.Push(ScriptObject::SizeOf(type)), value, type);
    }

    ScriptObject ScriptThread::Run(const Script::Function* function, int topIndex)
    {
        BinaryReader reader(stream);

        do
        {
            ProcessInstruction(reader);
        } while (stack.GetTopIndex() > topIndex && state == Running);

        if (state == Running)
        {
            ScriptObject result = ScriptObject::Void;
            if (function->ReturnTypes.size() > 0)
                result = ScriptObject::ReadFromBytes(stack.Peek(), function->ReturnTypes[0]);

            stack.Pop(function->ReturnTypes.size());

            state = Stopped;
            return result;
        }
        else
        {
            suspendedFunction = function;
            suspendedTopIndex = topIndex;
            return ScriptObject::Void;
        }
    }

    void ScriptThread::ProcessInstruction(BinaryReader& reader)
    {
        const ScriptInstruction id = static_cast<ScriptInstruction>(reader.ReadUInt8());
        switch (id)
        {
            case NOP:
                break;
            case Push1:
                reader.Read(stack.Push(1), 1);
                break;
            case Push4:
                reader.Read(stack.Push(4), 4);
                break;
            case Push8:
                reader.Read(stack.Push(8), 8);
                break;
            case Push12:
                reader.Read(stack.Push(12), 12);
                break;
            case Push16:
                reader.Read(stack.Push(16), 16);
                break;
            case PushN:
                {
                    const int size = static_cast<int>(reader.ReadInt32());
                    reader.Read(stack.Push(size), size);
                }
                break;
            case PushLocalVariable:
                {
                    const int stackIndex  = reader.ReadInt32();
                    const int localOffset = reader.ReadInt32();
                    const int size = reader.ReadInt32();
                    const byte* source = stack.GetAt(stackIndex);
                    Memory::Copy(stack.Push(size), size, &source[localOffset], size);
                }
                break;
            case PushGlobalVariable:
                {
                }
                break;
            case AllocateN:
                stack.Push(reader.ReadInt32());
                break;
            case Pop1:
                stack.Pop(1);
                break;
            case Pop2:
                stack.Pop(2);
                break;
            case Pop3:
                stack.Pop(3);
                break;
            case Pop4:
                stack.Pop(4);
                break;
            case PopN:
                stack.Pop(reader.ReadInt32());
                break;
            case Jump:
                {
                    const int32 newPosition = reader.ReadInt32();
                    reader.GetSource()->Seek(newPosition, Stream::FromBegin);
                }
                break;
            case IfFalseThenJump:
                {
                    const int32 newPosition = reader.ReadInt32();
                    const bool condition = BinaryReader::ToBool(stack.Peek());
                    stack.Pop(1);
                    if (condition == false)
                        reader.GetSource()->Seek(newPosition, Stream::FromBegin);
                }
                break;
            case CallScriptFunction:
                {
                    const int functionPosition = reader.ReadInt32();
                    const int numberOfArguments = static_cast<int>(reader.ReadInt32());
                    BinaryWriter::From(stack.Push(sizeof(int)), reader.GetSource()->GetPosition());
                    BinaryWriter::From(stack.Push(sizeof(int)), numberOfArguments); // Pop by ScriptInstruction::Return

                    reader.GetSource()->Seek(functionPosition, Stream::FromBegin);
                }
                break;
            case CallNativeFunction:
                {
                    const uint32 functionID = reader.ReadUInt32();
                    const int numberOfReturnValues = reader.ReadInt32();
                    const int numberOfArguments = reader.ReadInt32();
                    ScriptNativeFunction function = ScriptNativeFunctionTable::Find(functionID);

                    ScriptingContext context(this, numberOfArguments, numberOfReturnValues);
                    nativeFunctionDepth++;
                    function(context);
                    nativeFunctionDepth--;
                }
                break;
            case Return:
                {
                    // Expected stack layout (Bottom-up)
                    // ========================================
                    // [-1] Local variables
                    // [-2] Number of arguments
                    // [-3] Caller-address
                    // [-4 ~ ] Arguments 

                    const int position = BinaryReader::ToInt32(stack.GetAt(-3));
                    const int numberOfArguments = BinaryReader::ToInt32(stack.GetAt(-2));
                    stack.Pop(3 + numberOfArguments); // to "Return value spaces"
                    reader.GetSource()->Seek(position, Stream::FromBegin);
                }
                break;
            case Yield:
                {
                    // Script call -> Native call -> Script call -> Native 이 상황에서 Yield를 하면 thread-stack 엉켜 제대로 작동하지 않습니다.
                    BBAssert(nativeFunctionDepth == 0);
                    SetState(ScriptThread::Suspended);
                }
                break;
            case LocalAssign:
                {
                    const int stackIndex  = reader.ReadInt32();
                    const int localOffset = reader.ReadInt32();

                          byte* destination = stack.GetAt(stackIndex);
                          int   sourceSize = 0;
                    const byte* source = stack.Peek(sourceSize);
                    Memory::Copy(&destination[localOffset], sourceSize, source, sourceSize);

                    stack.Pop(1);
                }
                break;
            case GlobalAssign:
                {
                }
                break;
            case AddInt:
                {
                    const int operand1 = BinaryReader::ToInt32(stack.GetAt(-2));
                    const int operand2 = BinaryReader::ToInt32(stack.GetAt(-1));
                    stack.Pop(2);
                    BinaryWriter::From(stack.Push(sizeof(int)), static_cast<int>(operand1 + operand2));
                }
                break;
            case AddUInt:
                {
                }
                break;
            case AddLongInt:
                {
                }
                break;
            case AddFloat:
                {
                }
                break;
            case AddInt2:
                {
                }
                break;
            case AddInt3:
                {
                }
                break;
            case AddInt4:
                {
                }
                break;
            case AddFloat2:
                {
                }
                break;
            case AddFloat3:
                {
                }
                break;
            case AddFloat4:
                {
                }
                break;
            case SubtractInt:
                {
                    const int operand1 = BinaryReader::ToInt32(stack.GetAt(-2));
                    const int operand2 = BinaryReader::ToInt32(stack.GetAt(-1));
                    stack.Pop(2);
                    BinaryWriter::From(stack.Push(sizeof(int)), static_cast<int>(operand1 - operand2));
                }
                break;
            case SubtractUInt:
                {
                }
                break;
            case SubtractLongInt:
                {
                }
                break;
            case SubtractFloat:
                {
                }
                break;
            case SubtractInt2:
                {
                }
                break;
            case SubtractInt3:
                {
                }
                break;
            case SubtractInt4:
                {
                }
                break;
            case SubtractFloat2:
                {
                }
                break;
            case SubtractFloat3:
                {
                }
                break;
            case SubtractFloat4:
                {
                }
                break;
            case MultiplyInt:
                {
                    const int operand1 = BinaryReader::ToInt32(stack.GetAt(-2));
                    const int operand2 = BinaryReader::ToInt32(stack.GetAt(-1));
                    stack.Pop(2);
                    BinaryWriter::From(stack.Push(sizeof(int)), static_cast<int>(operand1 * operand2));
                }
                break;
            case TestEqualityInt:
                {
                    const int operand1 = BinaryReader::ToInt32(stack.GetAt(-2));
                    const int operand2 = BinaryReader::ToInt32(stack.GetAt(-1));
                    stack.Pop(2);
                    BinaryWriter::From(stack.Push(sizeof(bool)), static_cast<bool>(operand1 == operand2));
                }
                break;
            case TestInequalityInt:
                {
                    const int operand1 = BinaryReader::ToInt32(stack.GetAt(-2));
                    const int operand2 = BinaryReader::ToInt32(stack.GetAt(-1));
                    stack.Pop(2);
                    BinaryWriter::From(stack.Push(sizeof(bool)), static_cast<bool>(operand1 != operand2));
                }
                break;

        //    case NOPCommand:
        //        // 아무 것도 안합니다.
        //        break;
        //    case PushInt32Command:
        //        {
        //            stack.Push(reader.ReadInt32());
        //        }
        //        break;
        //    case PushUInt32Command:
        //        {
        //            stack.Push(reader.ReadUInt32());
        //        }
        //        break;
        //    case PushStringCommand:
        //        {
        //            stack.Push(reader.ReadString());
        //        }
        //        break;
        //    case PushLocalVariableCommand:
        //        {
        //            stack.Push(reader.ReadInt16());
        //        }
        //        break;
        //    case PushGlobalVariableCommand:
        //        {
        //            stack.Push(reader.ReadString());
        //        }
        //        break;
        //    case JumpCommand:
        //        {
        //        }
        //        break;
        //    case IfTrueThenJumpCommand:
        //        {
        //        }
        //        break;
        //    case IfFalseThenJumpCommand:
        //        {
        //        }
        //        break;
        //    case IfTrueThenJumpElseJumpCommand:
        //        {
        //        }
        //        break;
        //    case IfFalseThenJumpElseJumpCommand:
        //        {
        //        }
        //        break;
        //    case CallCommand:
        //        {
        //        }
        //        break;
        //    case CallNativeCommand:
        //        {
        //        }
        //        break;
        //    case ReturnCommand:
        //        {
        //        }
        //        break;
        //    case YieldCommand:
        //        {
        //        }
        //        break;
        //    case LocalAssignmentOperator:
        //        {
        //            const int16 localVariableIndex = reader.ReadInt16();
        //            ProcessInstruction(reader);
        //            stack.Peek(); // SET
        //            stack.Pop(1);
        //        }
        //        break;
        //    case GlobalAssignmentOperator:
        //        {
        //            stack.Push(reader.ReadString());
        //            ProcessInstruction(reader);
        //            stack.Peek().Value.CastTo<int32>();
        //            stack.Pop(1); // SET
        //        }
        //        break;
        //    case AdditionOperator:
        //        {
        //            ProcessInstruction(reader);
        //            ProcessInstruction(reader);
        //            ScriptStack::Item operand1 = stack.GetAt(-1);
        //            ScriptStack::Item operand2 = stack.GetAt(-2);
        //            stack.Pop(2);
        //            stack.Push(operand1.Value.CastTo<int32>() + operand2.Value.CastTo<int32>());
        //        }
        //        break;
        //    case EqualityOperator:
        //        {
        //        }
        //        break;
        //    case InequalityOperator:
        //        {
        //            ProcessInstruction(reader);
        //            ProcessInstruction(reader);
        //            ScriptStack::Item operand1 = stack.GetAt(-1);
        //            ScriptStack::Item operand2 = stack.GetAt(-2);
        //            stack.Pop(2);
        //            stack.Push(operand1.Value.CastTo<int32>() != operand2.Value.CastTo<int32>());
        //        }
        //        break;
        }
    }
}