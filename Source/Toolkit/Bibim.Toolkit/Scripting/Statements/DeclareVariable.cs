using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Scripting.Statements
{
    public sealed class DeclareVariable : Statement
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
                name = value ?? string.Empty;
            }
        }

        public ScriptObjectType Type
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public DeclareVariable()
            : this(string.Empty, ScriptObjectType.Void)
        {
        }

        public DeclareVariable(string name, ScriptObjectType type)
        {
            Name = name;
            Type = type;
        }
        #endregion

        #region Methods
        public override void Generate(ScriptCompiler.Context context)
        {
            // ... Compiler에서 구분용으로 쓰는 식별자이기 때문에 아무 명령도 생성하지 않습니다 ...
        }

        public static int SizeOf(ScriptObjectType type)
        {
            switch (type)
            {
                case ScriptObjectType.Void:
                    return 0;
                case ScriptObjectType.Bool:
                    return 1;
                case ScriptObjectType.Int:
                    return 4;
                case ScriptObjectType.LongInt:
                    return 4;
                case ScriptObjectType.Float:
                    return 4;
                case ScriptObjectType.Color:
                    return 4;
                case ScriptObjectType.Int2:
                    return 8;
                case ScriptObjectType.Int3:
                    return 12;
                case ScriptObjectType.Int4:
                    return 16;
                case ScriptObjectType.Float2:
                    return 8;
                case ScriptObjectType.Float3:
                    return 12;
                case ScriptObjectType.Float4:
                    return 16;
                case ScriptObjectType.String:
                default:
                    throw new NotSupportedException();
            }
        }
        #endregion
    }
}
