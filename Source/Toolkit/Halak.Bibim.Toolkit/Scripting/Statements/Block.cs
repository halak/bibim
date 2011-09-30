using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Script.Statements
{
    public sealed class Block : CompoundStatement
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
        {
            statements = new List<Statement>();
            readonlyStatements = new ReadOnlyCollection<Statement>(statements);
        }
        #endregion

        #region Constructors
        public void Add(Statement item)
        {
            if (item == null)
                throw new ArgumentNullException("item");

            statements.Add(item);
        }

        public void Insert(int index, Statement item)
        {
            if (item == null)
                throw new ArgumentNullException("item");

            statements.Insert(index, item);
        }

        public bool Remove(Statement item)
        {
            if (item != null)
                return statements.Remove(item);
            else
                return false;
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
    }
}
