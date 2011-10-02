using System;
using System.Collections.Generic;
using System.Text;

namespace Halak.Bibim.Scripting
{
    public sealed class ScriptProcess
    {
        public enum CommandID : byte
        {
            Jump = 0,
            IfTrueThenJump = 1,
            IfFalseThenJump = 2,
            IfTrueThenJumpElseJump = 3,
            IfFalseThenJumpElseJump = 4,
            Call = 5,
            CallNative = 6,
        }
    }
}
