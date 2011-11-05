using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Reflection;

namespace Bibim.Scripting.Statements
{
    public abstract class CallBase : Expression
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
        public void GeneratePushArguments(ScriptCompiler.Context context)
        {
            foreach (Expression item in Arguments)
                context.Generate(item);
        }
        #endregion
    }
}
