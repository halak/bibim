using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Halak.Bibim.Reflection;

namespace Halak.Bibim.Scripting.Statements
{
    public abstract class CallBase : Statement
    {
        #region Fields
        private string name;
        private Expression[] args;

        private static readonly Expression[] EmptyExpressions = new Expression[] { };
        #endregion

        #region Properties
        public string Name
        {
            get { return name; }
            set
            {
                name = value ?? string.Empty;
            }
        }

        public Expression[] Arguments
        {
            get { return args; }
            set
            {
                args = value ?? EmptyExpressions;
            }
        }
        #endregion

        #region Constructors
        public CallBase()
            : this(string.Empty, null)
        {
        }

        public CallBase(string name)
            : this(name, null)
        {
        }

        public CallBase(string name, Expression[] arguments)
        {
            Name = name;
            Arguments = arguments;
        }
        #endregion

        #region Methods
        public override void GenerateArguments(BinaryScriptGenerator.Context context)
        {
            context.Write(Arguments.Length);
            foreach (Expression item in Arguments)
                context.Write(item);
        }
        #endregion
    }
}
