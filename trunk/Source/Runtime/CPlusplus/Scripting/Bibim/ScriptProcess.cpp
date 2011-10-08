#include <Bibim/PCH.h>
#include <Bibim/ScriptProcess.h>
#include <Bibim/BinaryReader.h>
#include <Bibim/BinaryWriter.h>
#include <Bibim/Memory.h>
#include <Bibim/MemoryStream.h>
#include <Bibim/Script.h>
#include <Bibim/SCriptingContext.h>
#include <Bibim/ScriptNativeFunctionTable.h>

namespace Bibim
{
    enum ScriptCommandID
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
        IfTrueThenJump,
        IfTrueThenJumpElseJump,
        IfFalseThenJump,
        IfFalseThenJumpElseJump,
        Call,
        CallNative,
        Return,
        Yield,

        LocalAssign,
        GlobalAssign,
        AddInt,
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

    ScriptProcess::ScriptProcess(Script* script)
        : script(script),
          position(0)
    {
        if (script)
            position = script->GetEntryPoint();
    }

    ScriptProcess::ScriptProcess(Script* script, int stackSize)
        : script(script),
          position(0),
          stack(stackSize)
    {
    }

    ScriptProcess::~ScriptProcess()
    {
    }

    void ScriptProcess::Resume()
    {
        StreamPtr stream = MemoryStream::NewReadableStream(&script->GetBuffer()[0], script->GetBuffer().size());
        BinaryReader reader(stream);
        while (stream->GetPosition() < stream->GetLength())
            Process(reader);
    }

    void ScriptProcess::Suspend()
    {
    }

    void ScriptProcess::Process(BinaryReader& reader)
    {
        const ScriptCommandID id = static_cast<ScriptCommandID>(reader.ReadUInt8());
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
            case IfTrueThenJump:
                {
                    const int32 newPosition = reader.ReadInt32();
                    
                    Process(reader);

                    const bool condition = BinaryReader::ToBool(stack.Peek());
                    stack.Pop(1);
                    if (condition)
                        reader.GetSource()->Seek(newPosition, Stream::FromBegin);
                }
                break;
            case IfTrueThenJumpElseJump:
                {
                    const int32 newPosition1 = reader.ReadInt32();
                    const int32 newPosition2 = reader.ReadInt32();

                    Process(reader);

                    const bool condition = BinaryReader::ToBool(stack.Peek());
                    stack.Pop(1);
                    if (condition)
                        reader.GetSource()->Seek(newPosition1, Stream::FromBegin);
                    else
                        reader.GetSource()->Seek(newPosition2, Stream::FromBegin);
                }
                break;
            case IfFalseThenJump:
                {
                    const int32 newPosition = reader.ReadInt32();

                    Process(reader);

                    const bool condition = BinaryReader::ToBool(stack.Peek());
                    stack.Pop(1);
                    if (condition == false)
                        reader.GetSource()->Seek(newPosition, Stream::FromBegin);
                }
                break;
            case IfFalseThenJumpElseJump:
                {
                    const int32 newPosition1 = reader.ReadInt32();
                    const int32 newPosition2 = reader.ReadInt32();

                    Process(reader);

                    const bool condition = BinaryReader::ToBool(stack.Peek());
                    stack.Pop(1);
                    if (condition == false)
                        reader.GetSource()->Seek(newPosition1, Stream::FromBegin);
                    else
                        reader.GetSource()->Seek(newPosition2, Stream::FromBegin);
                }
                break;
            case Call:
                break;
            case CallNative:
                {
                    const uint32 functionID = reader.ReadUInt32();
                    const int32 numberOfArguments = reader.ReadInt32();
                    ScriptNativeFunction function = ScriptNativeFunctionTable::Find(functionID);

                    for (int i = 0; i < numberOfArguments; i++)
                        Process(reader);

                    // function();

                    stack.Pop(numberOfArguments);
                }
                break;
            case Return:
                {
                    Process(reader);
                    int result = BinaryReader::ToInt32(stack.Peek());
                    result = 0;
                }
                break;
            case Yield:
                break;
            case LocalAssign:
                {
                    const uint stackIndex  = reader.ReadInt32();
                    const uint localOffset = reader.ReadInt32();

                    Process(reader);

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
                    Process(reader);
                    Process(reader);
                    const int operand1 = BinaryReader::ToInt32(stack.GetAt(-2));
                    const int operand2 = BinaryReader::ToInt32(stack.GetAt(-1));
                    stack.Pop(2);
                    BinaryWriter::From(stack.Push(sizeof(int)), static_cast<int>(operand1 + operand2));
                }
                break;
            case TestEqualityInt:
                {
                    Process(reader);
                    Process(reader);
                    const int operand1 = BinaryReader::ToInt32(stack.GetAt(-2));
                    const int operand2 = BinaryReader::ToInt32(stack.GetAt(-1));
                    stack.Pop(2);
                    BinaryWriter::From(stack.Push(sizeof(bool)), static_cast<bool>(operand1 == operand2));
                }
                break;
            case TestInequalityInt:
                {
                    Process(reader);
                    Process(reader);
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
        //            Process(reader);
        //            stack.Peek(); // SET
        //            stack.Pop(1);
        //        }
        //        break;
        //    case GlobalAssignmentOperator:
        //        {
        //            stack.Push(reader.ReadString());
        //            Process(reader);
        //            stack.Peek().Value.CastTo<int32>();
        //            stack.Pop(1); // SET
        //        }
        //        break;
        //    case AdditionOperator:
        //        {
        //            Process(reader);
        //            Process(reader);
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
        //            Process(reader);
        //            Process(reader);
        //            ScriptStack::Item operand1 = stack.GetAt(-1);
        //            ScriptStack::Item operand2 = stack.GetAt(-2);
        //            stack.Pop(2);
        //            stack.Push(operand1.Value.CastTo<int32>() != operand2.Value.CastTo<int32>());
        //        }
        //        break;
        }
    }
}