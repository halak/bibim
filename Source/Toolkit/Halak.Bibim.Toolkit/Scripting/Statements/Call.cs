using System;
using System.Collections.Generic;
using System.Text;
using Halak.Bibim.IO;

namespace Halak.Bibim.Scripting.Statements
{
    public sealed class Call : CallBase
    {
        #region Constructors
        public Call()
        {
        }

        public Call(string name)
            : base(name)
        {
        }

        public Call(string name, Expression[] arguments)
            : base(name, arguments)
        {
        }
        #endregion

        public override void Generate(BinaryScriptGenerator.Context context)
        {
            context.WriteBibimString(Name);
            GenerateArguments(context);
        }
    }
}
