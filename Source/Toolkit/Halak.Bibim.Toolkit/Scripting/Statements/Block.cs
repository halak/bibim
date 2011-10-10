using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;

namespace Halak.Bibim.Scripting.Statements
{
    public class Block : Statement
    {
        #region Fields
        private List<Statement> statements;
        private ReadOnlyCollection<Statement> readonlyStatements;
        #endregion

        #region Properties
        public IList<Statement> Statements
        {
            get { return readonlyStatements; }
        }

        public Label StartLabel
        {
            get;
            private set;
        }

        public Label FinishLabel
        {
            get;
            private set;
        }
        #endregion

        #region Constructors
        public Block()
            : this(null)
        {
        }

        public Block(IEnumerable<Statement> statements)
        {
            if (statements == null)
                this.statements = new List<Statement>();
            else
                this.statements = new List<Statement>(statements);

            this.readonlyStatements = new ReadOnlyCollection<Statement>(this.statements);
            this.StartLabel = new Label();
            this.FinishLabel = new Label();
        }
        #endregion

        #region Sub-statement Manipulation (Methods)
        public void Add(Statement item)
        {
            statements.Add(item);
        }

        public void Insert(int index, Statement item)
        {            
            statements.Insert(index, item);
        }

        public bool Remove(Statement item)
        {
            return statements.Remove(item);
        }

        public void RemoveAt(int index)
        {            
            statements.RemoveAt(index);
        }

        public void Clear()
        {
            statements.Clear();
        }
        #endregion

        #region Generate (Methods)
        public sealed override void Generate(BinaryScriptGenerator.Context context)
        {
            GenerateBlockBefore(context);
            context.DeclareLabel(StartLabel);
            GenerateBlockBegin(context);

            foreach (Statement item in statements)
                context.Write(item);

            GenerateBlockEnd(context);
            context.DeclareLabel(FinishLabel);
            GenerateBlockAfter(context);
        }

        protected virtual void GenerateBlockBefore(BinaryScriptGenerator.Context context)
        {
        }

        protected virtual void GenerateBlockBegin(BinaryScriptGenerator.Context context)
        {
        }

        protected virtual void GenerateBlockEnd(BinaryScriptGenerator.Context context)
        {
        }

        protected virtual void GenerateBlockAfter(BinaryScriptGenerator.Context context)
        {
        }
       
        #endregion
    }
}
