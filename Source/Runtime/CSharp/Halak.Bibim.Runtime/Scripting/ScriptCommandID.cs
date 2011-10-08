using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Scripting
{
    public enum ScriptCommandID
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
    }
}
