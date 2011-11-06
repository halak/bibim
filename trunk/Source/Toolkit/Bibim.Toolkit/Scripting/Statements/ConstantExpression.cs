using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Bibim.IO;

namespace Bibim.Scripting.Statements
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
        public override void Generate(ScriptCompiler.Context context)
        {
            switch (Type.GetTypeCode(Value.GetType()))
            {
                case TypeCode.Empty:
                    throw new NotSupportedException();
                case TypeCode.Object:
                    Type type = Value.GetType();
                    if (type == typeof(Color))
                        context.Push((Color)Value);
                    else if (type == typeof(Vector2))
                        context.Push((Vector2)Value);
                    else if (type == typeof(Vector3))
                        context.Push((Vector3)Value);
                    else if (type == typeof(Vector4))
                        context.Push((Vector4)Value);
                    else
                        throw new InvalidOperationException();
                    break;
                case TypeCode.DBNull:
                    throw new NotSupportedException();
                case TypeCode.Boolean:
                    context.Push((bool)Value);
                    break;
                case TypeCode.Char:
                case TypeCode.SByte:
                case TypeCode.Byte:
                case TypeCode.Int16:
                case TypeCode.UInt16:
                case TypeCode.Int32:
                    context.Push(Convert.ToInt32(Value));
                    break;
                case TypeCode.UInt32:
                    context.Push(Convert.ToUInt32(Value));
                    break;
                case TypeCode.Int64:
                case TypeCode.UInt64:
                    context.Push(Convert.ToInt64(Value));
                    break;
                case TypeCode.Single:
                case TypeCode.Double:
                    context.Push(Convert.ToSingle(Value));
                    break;
                case TypeCode.Decimal:
                    throw new InvalidOperationException();
                case TypeCode.DateTime:
                    throw new InvalidOperationException();
                case TypeCode.String:
                    context.Push((string)Value);
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

        private static int GetBibimStringBytes(string value)
        {
            byte[] bytes = Encoding.UTF8.GetBytes(value);
            return 4 + bytes.Length; // 4 == sizeof(int)
        }
        #endregion
    }
}
