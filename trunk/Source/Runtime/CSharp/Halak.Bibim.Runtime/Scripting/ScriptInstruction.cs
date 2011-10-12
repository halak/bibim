using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Scripting
{
    public enum ScriptInstruction
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
    }
}
