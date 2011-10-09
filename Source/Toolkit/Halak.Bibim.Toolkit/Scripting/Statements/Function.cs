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

        public IList<ScriptObjectType> ReturnTypes
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
        public Function(string name, IEnumerable<DeclareVariable> parameters, IEnumerable<ScriptObjectType> returnTypes, IEnumerable<Statement> statements)
            : base(statements)
        {
            this.name = name ?? string.Empty;
            if (parameters != null)
                this.Parameters = new List<DeclareVariable>(parameters);
            else
                this.Parameters = new List<DeclareVariable>();
            if (returnTypes != null)
                this.ReturnTypes = new List<ScriptObjectType>(returnTypes);
            else
                this.ReturnTypes = new List<ScriptObjectType>();
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
        #endregion
    }
}
