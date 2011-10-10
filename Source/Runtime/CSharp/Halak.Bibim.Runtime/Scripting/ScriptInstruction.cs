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
        SubtractInt,
        MultiplyInt,
        TestEqualityInt,
        TestInequalityInt,
    }
}
