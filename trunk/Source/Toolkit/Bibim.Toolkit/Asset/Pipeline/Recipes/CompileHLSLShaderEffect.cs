using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Asset.Pipeline.Recipes
{
    public sealed class CompileHLSLShaderEffect : CompileShaderEffect
    {
        #region Constructors
        public CompileHLSLShaderEffect()
            : base()
        {
        }

        public CompileHLSLShaderEffect(string input)
            : base(input)
        {
        }

        public CompileHLSLShaderEffect(string input, string defines)
            : base(input, defines)
        {
        }
        #endregion

        protected override string Preprocess(Dictionary<string, string> defines, IList<string> codeLines)
        {
            StringBuilder outputString = new StringBuilder();
            foreach (var item in defines)
            {
                if (string.IsNullOrEmpty(item.Value))
                    outputString.AppendLine(string.Format("#define {0}", item.Key));
                else
                    outputString.AppendLine(string.Format("#define {0} {1}", item.Key, item.Value));
            }

            foreach (var item in codeLines)
                outputString.AppendLine(item);

            return outputString.ToString();
        }
    }
}
