using System;
using System.Collections.Generic;
using System.Text;

namespace Halak.Bibim.Scripting
{
    public sealed class ScriptProcess
    {
        public enum CommandID : byte
        {
            NOP,
            PushInt32,
            PushUInt32,
            PushString,
            Jump,
            IfTrueThenJump,
            IfFalseThenJump,
            IfTrueThenJumpElseJump,
            IfFalseThenJumpElseJump,
            Call,
            CallNative,
            Return,
            Yield,

            LocalAssignmentOperator,
            GlobalAssignmentOperator,
            AdditionOperator,
            EqualityOperator,
            InequalityOperator,
        }
    }
}
