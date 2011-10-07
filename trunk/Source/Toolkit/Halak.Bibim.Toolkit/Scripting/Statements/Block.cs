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
            if (item == null)
                throw new ArgumentNullException("item");

            Statement last = null;
            if (statements.Count > 0)
            {
                last = statements[statements.Count - 1];
                last.Next = item;
            }

            item.Previous = last;
            item.Next = null;
            statements.Add(item);
        }

        public void Insert(int index, Statement item)
        {
            if (item == null)
                throw new ArgumentNullException("item");
            if (0 <= index && index < statements.Count)
                throw new ArgumentOutOfRangeException("index");

            Statement after = statements[index];

            if (after.Previous != null)
                after.Previous.Next = item;
            item.Previous = after.Previous;
            item.Next = after;
            after.Previous = item;

            statements.Insert(index, item);
        }

        public bool Remove(Statement item)
        {
            int index = statements.IndexOf(item);
            if (index != -1)
            {
                RemoveAt(index);
                return true;
            }
            else
                return false;
        }

        public void RemoveAt(int index)
        {
            Statement item = statements[index];

            if (item.Previous != null)
                item.Previous.Next = item.Next;
            if (item.Next != null)
                item.Next.Previous = item.Previous;

            item.Previous = null;
            item.Next = null;

            statements.RemoveAt(index);
        }

        public void Clear()
        {
            foreach (Statement item in statements)
            {
                item.Previous = null;
                item.Next = null;
            }

            statements.Clear();
        }
        #endregion

        #region Generate (Methods)
        public override void Generate(BinaryScriptGenerator.Context context)
        {
            foreach (Statement item in statements)
                context.Write(item);
        }
        #endregion
    }
}
