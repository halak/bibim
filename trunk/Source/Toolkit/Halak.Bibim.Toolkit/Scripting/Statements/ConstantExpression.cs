using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Halak.Bibim.IO;

namespace Halak.Bibim.Scripting.Statements
{
    public sealed class ConstantExpression : Expression
    {
        #region Properties
        public object Value
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public ConstantExpression()
            : this(null)
        {
        }

        public ConstantExpression(object value)
        {
            Value = value;
        }
        #endregion

        #region Methods
        public override void Generate(BinaryScriptGenerator.Context context)
        {
            switch (Type.GetTypeCode(Value.GetType()))
            {
                case TypeCode.Empty:
                    throw new InvalidOperationException();
                case TypeCode.Object:
                    throw new InvalidOperationException();
                case TypeCode.DBNull:
                    throw new InvalidOperationException();
                case TypeCode.Boolean:
                    context.Write(ScriptProcess.CommandID.PushUInt32);
                    context.Write((bool)Value);
                    break;
                case TypeCode.Char:
                    throw new InvalidOperationException();
                case TypeCode.SByte:
                    context.Write(ScriptProcess.CommandID.PushUInt32);
                    context.Write((sbyte)Value);
                    break;
                case TypeCode.Byte:
                    context.Write(ScriptProcess.CommandID.PushUInt32);
                    context.Write((byte)Value);
                    break;
                case TypeCode.Int16:
                    context.Write(ScriptProcess.CommandID.PushUInt32);
                    context.Write((short)Value);
                    break;
                case TypeCode.UInt16:
                    context.Write(ScriptProcess.CommandID.PushUInt32);
                    context.Write((ushort)Value);
                    break;
                case TypeCode.Int32:
                    context.Write(ScriptProcess.CommandID.PushInt32);
                    context.Write((int)Value);
                    break;
                case TypeCode.UInt32:
                    context.Write(ScriptProcess.CommandID.PushUInt32);
                    context.Write((uint)Value);
                    break;
                case TypeCode.Int64:
                    context.Write(ScriptProcess.CommandID.PushUInt32);
                    context.Write((uint)Value);
                    break;
                case TypeCode.UInt64:
                    context.Write(ScriptProcess.CommandID.PushUInt32);
                    context.Write((uint)Value);
                    break;
                case TypeCode.Single:
                    context.Write(ScriptProcess.CommandID.PushUInt32);
                    context.Write((uint)Value);
                    break;
                case TypeCode.Double:
                    context.Write(ScriptProcess.CommandID.PushUInt32);
                    context.Write((uint)Value);
                    break;
                case TypeCode.Decimal:
                    throw new InvalidOperationException();
                case TypeCode.DateTime:
                    throw new InvalidOperationException();
                case TypeCode.String:
                    context.Write(ScriptProcess.CommandID.PushString);
                    context.WriteBibimString((string)Value);
                    break;
            }
        }

        public override string ToString()
        {
            if (Value != null)
                return Value.ToString();
            else
                return "(null)";
        }
        #endregion
    }
}
