#include <Bibim/PCH.h>
#include <Bibim/ScriptProcess.h>
#include <Bibim/BinaryReader.h>
#include <Bibim/MemoryStream.h>
#include <Bibim/Script.h>
#include <Bibim/SCriptingContext.h>

namespace Bibim
{
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
        Process(reader);
    }

    void ScriptProcess::Suspend()
    {
    }

    void ScriptProcess::Process(BinaryReader& reader)
    {
        const CommandID id = static_cast<CommandID>(reader.ReadUInt8());
        switch (id)
        {
            case NOPCommand:
                // 아무 것도 안합니다.
                break;
            case PushInt32Command:
                {
                    stack.Push(reader.ReadInt32());
                }
                break;
            case PushUInt32Command:
                {
                    stack.Push(reader.ReadUInt32());
                }
                break;
            case PushStringCommand:
                {
                    stack.Push(reader.ReadString());
                }
                break;
            case PushLocalVariableCommand:
                {
                    stack.Push(reader.ReadInt16());
                }
                break;
            case PushGlobalVariableCommand:
                {
                    stack.Push(reader.ReadString());
                }
                break;
            case JumpCommand:
                {
                }
                break;
            case IfTrueThenJumpCommand:
                {
                }
                break;
            case IfFalseThenJumpCommand:
                {
                }
                break;
            case IfTrueThenJumpElseJumpCommand:
                {
                }
                break;
            case IfFalseThenJumpElseJumpCommand:
                {
                }
                break;
            case CallCommand:
                {
                }
                break;
            case CallNativeCommand:
                {
                }
                break;
            case ReturnCommand:
                {
                }
                break;
            case YieldCommand:
                {
                }
                break;
            case LocalAssignmentOperator:
                {
                    const int16 localVariableIndex = reader.ReadInt16();
                    Process(reader);
                    stack.Peek(); // SET
                    stack.Pop(1);
                }
                break;
            case GlobalAssignmentOperator:
                {
                    stack.Push(reader.ReadString());
                    Process(reader);
                    stack.Peek().Value.CastTo<int32>();
                    stack.Pop(1); // SET
                }
                break;
            case AdditionOperator:
                {
                    Process(reader);
                    Process(reader);
                    ScriptStack::Item operand1 = stack.GetAt(-1);
                    ScriptStack::Item operand2 = stack.GetAt(-2);
                    stack.Pop(2);
                    stack.Push(operand1.Value.CastTo<int32>() + operand2.Value.CastTo<int32>());
                }
                break;
            case EqualityOperator:
                {
                }
                break;
            case InequalityOperator:
                {
                    Process(reader);
                    Process(reader);
                    ScriptStack::Item operand1 = stack.GetAt(-1);
                    ScriptStack::Item operand2 = stack.GetAt(-2);
                    stack.Pop(2);
                    stack.Push(operand1.Value.CastTo<int32>() != operand2.Value.CastTo<int32>());
                }
                break;
        }
    }
}