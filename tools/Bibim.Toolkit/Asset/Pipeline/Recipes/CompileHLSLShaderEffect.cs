using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
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

        protected override Tuple<byte[], int> Compile(string code)
        {
            string input = Path.GetTempFileName();
            string output = Path.GetTempFileName();

            using (var fs = new FileStream(input, FileMode.Create, FileAccess.Write))
            using (var sw = new StreamWriter(fs))
            {
                sw.Write(code);
            }

            string args = string.Format("/T fx_2_0 /Fo \"{1}\" /O3 /nologo \"{0}\"", input, output);

            ProcessStartInfo start = new ProcessStartInfo(@"Plugin\fxc.exe", args)
            {
                CreateNoWindow = true,
                UseShellExecute = false,
                RedirectStandardOutput = true,
                RedirectStandardError = true,
            };
            Process process = Process.Start(start);
            process.WaitForExit();

            string compileMessage = process.StandardOutput.ReadToEnd();
            string compileErrorMessage = process.StandardError.ReadToEnd();

            if (string.IsNullOrEmpty(compileErrorMessage))
            {
                Trace.WriteLine(string.Format("Compile result\n{0}", compileMessage));

                byte[] buffer = null;
                using (var fs = new FileStream(output, FileMode.Open, FileAccess.Read))
                {
                    BinaryReader fxoReader = new BinaryReader(fs);
                    buffer = fxoReader.ReadBytes((int)fs.Length);
                }

                return Tuple.Create(buffer, 0);
            }
            else
            {
                throw new InvalidDataException(string.Format("Compile failure.\n{0}\n{1}\n{2}", compileMessage, compileErrorMessage, args));
            }
        }
    }
}
