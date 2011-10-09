using System;
using System.Collections.Generic;
using System.Text;

namespace Halak.Bibim.Scripting.Statements
{
    public sealed class Function : Block
    {
        #region Fields
        private string name;
        #endregion

        #region Properties
        public string Name
        {
            get { return name; }
            set
            {
                if (name != value)
                {
                    name = value ?? string.Empty;
                }
            }
        }

        public IList<DeclareVariable> Parameters
        {
            get;
            set;
        }

        public ScriptObjectType ReturnType
        {
            get;
            set;
        }

        public Label StartLabel
        {
            get;
            private set;
        }
        #endregion

        #region Constructors
        public Function()
            : this(string.Empty, ScriptObjectType.Void, null, null)
        {
        }

        public Function(string name)
            : this(name, ScriptObjectType.Void, null, null)
        {
        }

        public Function(string name, IEnumerable<Statement> statements)
            : this(name, ScriptObjectType.Void, null, statements)
        {
        }

        public Function(string name, ScriptObjectType returnType)
            : this(name, returnType, null, null)
        {
        }

        public Function(string name, IEnumerable<DeclareVariable> parameters)
            : this(name, ScriptObjectType.Void, parameters, null)
        {
        }

        public Function(string name, ScriptObjectType returnType, IEnumerable<Statement> statements)
            : this(name, returnType, null, statements)
        {
        }

        public Function(string name, IEnumerable<DeclareVariable> parameters, IEnumerable<Statement> statements)
            : this(name, ScriptObjectType.Void, parameters, statements)
        {
        }

        public Function(string name, ScriptObjectType returnType, IEnumerable<DeclareVariable> parameters, IEnumerable<Statement> statements)
            : base(statements)
        {
            this.name = name ?? string.Empty;
            this.ReturnType = returnType;
            if (parameters != null)
                this.Parameters = new List<DeclareVariable>(parameters);
            else
                this.Parameters = new List<DeclareVariable>();
            this.StartLabel = new Label();
        }
        #endregion

        #region Methods
        public override void Generate(BinaryScriptGenerator.Context context)
        {
            context.WriteLabel(StartLabel);

            int requiredStackSize = ComputeRequiredStackSize();
            if (requiredStackSize > 0)
            {
                context.Write(ScriptCommandID.AllocateN);
                context.Write(ComputeRequiredStackSize());
            }

            base.Generate(context);

            if (requiredStackSize > 0)
                context.Write(ScriptCommandID.Pop1);
        }

        protected override int ComputeRequiredStackSize()
        {
            int result = base.ComputeRequiredStackSize();

            if (Parameters != null)
            {
                foreach (DeclareVariable item in Parameters)
                    result += DeclareVariable.SizeOf(item.Type);
            }

            return result;
        }
        #endregion
    }
}
