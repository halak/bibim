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
                    throw new NotSupportedException();
                case TypeCode.Object:
                    throw new NotSupportedException();
                case TypeCode.DBNull:
                    throw new NotSupportedException();
                case TypeCode.Boolean:
                    context.GeneratePushValue(BitConverter.GetBytes((bool)Value));
                    break;
                case TypeCode.Char:
                case TypeCode.SByte:
                case TypeCode.Byte:
                case TypeCode.Int16:
                case TypeCode.UInt16:
                case TypeCode.Int32:
                    context.GeneratePushValue(BitConverter.GetBytes(Convert.ToInt32(Value)));
                    break;
                case TypeCode.UInt32:
                    context.GeneratePushValue(BitConverter.GetBytes(Convert.ToUInt32(Value)));
                    break;
                case TypeCode.Int64:
                case TypeCode.UInt64:
                    context.GeneratePushValue(BitConverter.GetBytes(Convert.ToInt64(Value)));
                    break;
                case TypeCode.Single:
                case TypeCode.Double:
                    context.GeneratePushValue(BitConverter.GetBytes(Convert.ToSingle(Value)));
                    break;
                case TypeCode.Decimal:
                    throw new InvalidOperationException();
                case TypeCode.DateTime:
                    throw new InvalidOperationException();
                case TypeCode.String:
                    throw new InvalidOperationException();
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
