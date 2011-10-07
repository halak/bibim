using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;
using Halak.Bibim.Scripting.Statements;

namespace Halak.Bibim.Scripting
{
    public class BinaryScriptGenerator
    {
        #region Fields
        #endregion

        #region Properties
        #endregion

        #region Constructors
        public BinaryScriptGenerator()
        {
        }
        #endregion

        #region Methods
        public void Generate(Stream output, Statement statement)
        {
            if (output == null)
                throw new ArgumentNullException("output");
            if (statement == null)
                throw new ArgumentNullException("statement");

            Context context = new Context(this, output);
            statement.Generate(context);
        }

        private void Generate(Context context)
        {
            Block block = context.Current as Block;
            if (block != null)
            {
                OnEnter(context, block);
                foreach (Statement item in block.Statements)
                {
                    context.Push(item);
                    Generate(context);
                    context.Pop();
                }
                OnExit(context, block);
            }
            else
                OnVisit(context, context.Current);
        }
        #endregion

        #region Protected Methods
        protected virtual void OnVisit(Context context, Statement statement)
        {
        }

        protected virtual void OnEnter(Context context, Block block)
        {
        }

        protected virtual void OnExit(Context context, Block block)
        {
        }
        #endregion

        #region Context (Nested Class)
        public class Context
        {
            #region Fields
            private Stack<Statement> stack;
            #endregion

            #region Properties
            public Stream Output
            {
                get;
                private set;
            }

            public Statement Root
            {
                get;
                private set;
            }

            public Statement Current
            {
                get
                {
                    Trace.Assert(stack.Count > 0);
                    return stack.Peek();
                }
            }
            #endregion

            #region Constructors
            public Context(BinaryScriptGenerator generator, Stream output)
            {
                Trace.Assert(output != null && output.CanWrite);

                Output = output;
                stack = new Stack<Statement>();
            }
            #endregion

            #region Methods
            public void Push(Statement statement)
            {
                if (stack.Count == 0)
                    Root = statement;

                stack.Push(statement);
            }

            public void Pop()
            {
                stack.Pop();

                if (stack.Count == 0)
                    Root = null;
            }
            #endregion
        }
        #endregion
    }
}
