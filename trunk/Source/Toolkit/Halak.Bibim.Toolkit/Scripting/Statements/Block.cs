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
        public override void Generate(BinaryScriptGenerator.Context context)
        {
            foreach (Statement item in statements)
                context.Write(item);
        }
        
        protected virtual int ComputeRequiredStackSize()
        {
            int result = 0;
            foreach (Statement item in statements)
            {
                Block block = item as Block;
                DeclareVariable variableDeclaration = item as DeclareVariable;
                if (block != null)
                    result += block.ComputeRequiredStackSize();
                if (variableDeclaration != null)
                    result += DeclareVariable.SizeOf(variableDeclaration.Type);
            }

            return result;
        }
        #endregion
    }
}
