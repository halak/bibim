using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Halak.Bibim.Reflection;

namespace Halak.Bibim.Scripting.Statements
{
    public sealed class CallNative : CallBase
    {
        #region Constructors
        public CallNative()
        {
        }

        public CallNative(string name)
            : base(name)
        {
        }

        public CallNative(string name, Expression[] arguments)
            : base(name, arguments)
        {
        }

        public CallNative(string name, Expression arg1)
            : this(name, new Expression[] { arg1 })
        {
        }

        public CallNative(string name, Expression arg1, Expression arg2)
            : this(name, new Expression[] { arg1, arg2 })
        {
        }

        public CallNative(string name, Expression arg1, Expression arg2, Expression arg3)
            : this(name, new Expression[] { arg1, arg2, arg3 })
        {
        }

        public CallNative(string name, Expression arg1, Expression arg2, Expression arg3, Expression arg4)
            : this(name, new Expression[] { arg1, arg2, arg3, arg4 })
        {
        }

        public CallNative(string name, Expression arg1, Expression arg2, Expression arg3, Expression arg4, Expression arg5)
            : this(name, new Expression[] { arg1, arg2, arg3, arg4, arg5 })
        {
        }
        #endregion

        public override void Generate(BinaryScriptGenerator.Context context)
        {
            throw new NotImplementedException();
        }
    }
}
