using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;

namespace Bibim.Asset.Pipeline.Recipes
{
    public sealed class CompileHexData : CookingNode<StreamingGameAsset>
    {
        #region Properties
        public string Data
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public CompileHexData()
        {
        }

        public CompileHexData(string data)
        {
            this.Data = data ?? string.Empty;
        }
        #endregion

        public sealed override StreamingGameAsset Cook(CookingContext context)
        {
            var binaryData = new byte[Data.Length / 2];

            for (int i = 0, k = 0; i < Data.Length; i += 2, k++)
            {
                int upper = Convert(Data[i + 0]);
                int lower = Convert(Data[i + 1]);
                binaryData[k] = (byte)(((upper << 4) & 0xF0) | ((lower << 0) & 0x0F));
            }

            return new StreamingGameAsset(binaryData);
        }

        private static int Convert(char c)
        {
            if ('0' <= c && c <= '9')
                return c - '0';
            else if ('A' <= c && c <= 'F')
                return c - 'A' + 10;
            else if ('a' <= c && c <= 'f')
                return c - 'a' + 10;
            else
                throw new InvalidDataException(string.Format("not allowed character: {0}", c));
        }
    }
}
