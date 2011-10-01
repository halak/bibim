using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using Halak.Bibim.Scripting.Statements;

namespace Halak.Bibim.Scripting.Generators
{
    public class BinaryScriptGenerator : ScriptGenerator
    {
        #region Constructors
        public BinaryScriptGenerator()
        {
        }
        #endregion

        #region Methods
        protected override ScriptGenerator.Context CreateContext(Stream outputStream)
        {
            return new Context(outputStream);
        }

        protected override void OnVisit(ScriptGenerator.Context context, Statement statement)
        {
            Context cc = (Context)context;
        }

        protected override void OnEnter(ScriptGenerator.Context context, Block block)
        {
            Context cc = (Context)context;
        }

        protected override void OnExit(ScriptGenerator.Context context, Block block)
        {
            Context cc = (Context)context;
        }
        #endregion

        #region Context (Nested Class)
        private new sealed class Context : ScriptGenerator.Context
        {
            #region Properties
            public Writer Writer
            {
                get;
                private set;
            }
            #endregion

            #region Constructor
            public Context(Stream output)
                : base(output)
            {
                Writer = new Writer(output);
            }
            #endregion
        }
        #endregion

        #region Writer (Nested Class)
        private sealed class Writer : BinaryWriter
        {
            #region Constructor
            public Writer(Stream output)
                : base(output)
            {
                Trace.Assert(output.CanSeek);
            }
            #endregion

            #region Methods
            #endregion
        }
        #endregion
    }
}
