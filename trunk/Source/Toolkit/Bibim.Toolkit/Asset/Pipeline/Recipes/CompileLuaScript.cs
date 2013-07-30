using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;

namespace Bibim.Asset.Pipeline.Recipes
{
    public sealed class CompileLuaScript : CookingNode<StreamingGameAsset>
    {
        #region Properties
        public string Input
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public CompileLuaScript()
        {
        }

        public CompileLuaScript(string input)
        {
            this.Input = input ?? string.Empty;
        }
        #endregion

        public sealed override StreamingGameAsset Cook(CookingContext context)
        {
            string assetPath = Path.Combine(context.Directory, context.ExpandVariables(Input));
            string input = Path.Combine(context.BaseDirectory, assetPath);
            if (File.Exists(input) == false)
                throw new FileNotFoundException(string.Empty, input);

            context.AddDependency(input);

            string output = Path.GetTempFileName();
            string args = string.Format("-o \"{1}\" \"{0}\"", input, output);

            ProcessStartInfo start = new ProcessStartInfo(@"Plugin\luac52.exe", args)
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
                byte[] buffer = null;
                using (var fs = new FileStream(output, FileMode.Open, FileAccess.Read))
                {
                    BinaryReader reader = new BinaryReader(fs);
                    buffer = reader.ReadBytes((int)fs.Length);
                }

                return new StreamingGameAsset(buffer);
            }
            else
            {
                throw new InvalidDataException(string.Format("Compile failure.\n{0}\n{1}\n{2}", compileMessage, compileErrorMessage, args));
            }
        }
    }
}
