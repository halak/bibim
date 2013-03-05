using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Asset.Pipeline.Recipes
{
    public sealed class CompileGLSLShaderEffect : CompileShaderEffect
    {
        #region Constructors
        public CompileGLSLShaderEffect()
            : base()
        {
        }

        public CompileGLSLShaderEffect(string input)
            : base(input)
        {
        }

        public CompileGLSLShaderEffect(string input, string defines)
            : base(input, defines)
        {
        }
        #endregion

        protected override string Preprocess(Dictionary<string, string> defines, IList<string> codeLines)
        {
            int index = GetBoundariesOfVSAndFS(codeLines);
            if (index == -1)
                return string.Empty;

            InsertDefines(codeLines, index + 1, defines);
            InsertDefines(codeLines, 0, defines);

            StringBuilder outputString = new StringBuilder();
            foreach (var item in codeLines)
                outputString.AppendLine(item);

            return outputString.ToString();
        }

        private static void InsertDefines(IList<string> codeLines, int index, Dictionary<string, string> defines)
        {
            foreach (var item in defines)
            {
                if (string.IsNullOrEmpty(item.Value))
                    codeLines.Insert(index, string.Format("#define {0}", item.Key));
                else
                    codeLines.Insert(index, string.Format("#define {0} {1}", item.Key, item.Value));
            }
        }

        private static int GetBoundariesOfVSAndFS(IList<string> codeLines)
        {
            for (int i = 0; i < codeLines.Count; i++)
            {
                if (codeLines[i].Contains("//////////"))
                {
                    return i;
                }
            }

            return -1;
        }
    }
}
