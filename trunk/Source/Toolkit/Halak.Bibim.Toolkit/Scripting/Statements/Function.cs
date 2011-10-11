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
                value = value ?? string.Empty;

                if (name != value)
                {
                    name = value;

                    BeginLabel.Name = string.Format("Function {0}", name);
                    EndLabel.Name = string.Format("End Function {0}", name);
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
        #endregion

        #region Constructors
        public Function(string name)
            : this(name, null, null, null)
        {
        }

        public Function(string name, IEnumerable<DeclareVariable> parameters, IEnumerable<ScriptObjectType> returnTypes, IEnumerable<Statement> statements)
            : base(statements)
        {
            this.Name = name ?? string.Empty;
            if (parameters != null)
                this.Parameters = new List<DeclareVariable>(parameters);
            else
                this.Parameters = new List<DeclareVariable>();
            if (returnTypes != null)
                this.ReturnTypes = new List<ScriptObjectType>(returnTypes);
            else
                this.ReturnTypes = new List<ScriptObjectType>();
        }
        #endregion

        #region Methods
        protected override void GenerateBlockBegin(ScriptCompiler.Context context)
        {
            context.Function(ComputeRequiredStackSize(true));
        }
        #endregion
    }
}
