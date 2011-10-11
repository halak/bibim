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

        public Label BeginLabel
        {
            get;
            private set;
        }

        public Label EndLabel
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
            this.BeginLabel = new Label();
            this.EndLabel = new Label();
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

        public IList<Statement> FindAll(Predicate<Statement> match)
        {
            List<Statement> result = new List<Statement>();
            FindAll(result, this, match);
            return result;
        }

        public Statement Find(Predicate<Statement> match)
        {
            return Find(this, match);
        }

        private static void FindAll(List<Statement> result, Block block, Predicate<Statement> match)
        {
            if (match(block))
                result.Add(block);

            foreach (Statement item in block.statements)
            {
                if (item is Block)
                    FindAll(result, (Block)item, match);
                else
                {
                    if (match(item))
                        result.Add(item);
                }
            }
        }

        private static Statement Find(Block block, Predicate<Statement> match)
        {
            if (match(block))
                return block;

            foreach (Statement item in block.statements)
            {
                if (item is Block)
                {
                    Statement found = Find((Block)item, match);
                    if (found != null)
                        return found;
                }
                else
                {
                    if (match(item))
                        return item;
                }
            }

            return null;
        }
        #endregion

        #region Generate (Methods)
        public sealed override void Generate(ScriptCompiler.Context context)
        {
            GenerateBlockBefore(context);
            context.InidicateLabel(BeginLabel);
            GenerateBlockBegin(context);
            
            foreach (Statement item in statements)
                context.Generate(item);
            
            GenerateBlockEnd(context);
            context.InidicateLabel(EndLabel);
            GenerateBlockAfter(context);
        }

        protected virtual void GenerateBlockBefore(ScriptCompiler.Context context)
        {
        }

        protected virtual void GenerateBlockBegin(ScriptCompiler.Context context)
        {
        }

        protected virtual void GenerateBlockEnd(ScriptCompiler.Context context)
        {
        }

        protected virtual void GenerateBlockAfter(ScriptCompiler.Context context)
        {
        }

        public int ComputeRequiredStackSize(bool recursively)
        {
            int result = 0;
            foreach (Statement item in statements)
            {
                if (item is DeclareVariable)
                    result += DeclareVariable.SizeOf(((DeclareVariable)item).Type);

                if (recursively)
                {
                    Block block = item as Block;
                    if (block != null)
                        result += block.ComputeRequiredStackSize(true);
                }
            }

            return result;
        }

        public IList<DeclareVariable> GetVariableDeclarations(bool recursively)
        {
            List<DeclareVariable> result = new List<DeclareVariable>();
            GetVariableDeclarations(result, this, recursively);
            return result;
        }

        private static void GetVariableDeclarations(List<DeclareVariable> declarations, Block block, bool recursively)
        {
            foreach (Statement item in block.statements)
            {
                if (item is DeclareVariable)
                    declarations.Add((DeclareVariable)item);

                if (recursively)
                {
                    Block subBlock = item as Block;
                    if (subBlock != null)
                        GetVariableDeclarations(declarations, subBlock, recursively);
                }
            }
        }
        #endregion
    }
}
