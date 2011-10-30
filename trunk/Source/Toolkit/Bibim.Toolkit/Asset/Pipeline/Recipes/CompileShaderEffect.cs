using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using Bibim.Graphics;

namespace Bibim.Asset.Pipeline.Recipes
{
    public sealed class CompileShaderEffect : CookingNode<ShaderEffect>
    {
        #region Properties
        [XmlAttribute]
        public string Input
        {
            get;
            set;
        }
        #endregion

        #region Constructor
        public CompileShaderEffect()
            : this(string.Empty)
        {
        }

        public CompileShaderEffect(string input)
        {
            Input = input ?? string.Empty;
        }
        #endregion

        public override ShaderEffect Cook(CookingContext context)
        {
            string assetPath = Path.Combine(context.Directory, context.ExpandVariables(Input));
            string input = Path.Combine(context.BaseDirectory, assetPath);
            if (File.Exists(input) == false)
                throw new FileNotFoundException(string.Empty, input);

            context.AddDependency(input);
            string outputFXOFileName = Path.GetTempFileName();

            string args = string.Format("/T fx_2_0 /Fo \"{1}\" /Zi /nologo \"{0}\"", input, outputFXOFileName);

            ProcessStartInfo start = new ProcessStartInfo(@"Plugin\fxc.exe", args)
            {
                CreateNoWindow = false,
                UseShellExecute = false,
                RedirectStandardOutput = true,
                RedirectStandardError = true,
            };
            Process process = Process.Start(start);
            process.WaitForExit();

            string compileMessage = process.StandardOutput.ReadToEnd();
            string compileErrorMessage = process.StandardError.ReadToEnd().Replace(input, assetPath);

            if (string.IsNullOrEmpty(compileErrorMessage))
            {
                Trace.WriteLine(string.Format("Compile result\n{0}", compileMessage));

                byte[] buffer = null;
                using (var fs = new FileStream(outputFXOFileName, FileMode.Open, FileAccess.Read))
                {
                    BinaryReader fxoReader = new BinaryReader(fs);
                    buffer = fxoReader.ReadBytes((int)fs.Length);
                }

                File.Delete(outputFXOFileName);

                return new ShaderEffect(null)
                {
                    Tag = new ShaderEffectCookingTag(buffer)
                };
            }
            else
            {
                File.Delete(outputFXOFileName);
                throw new InvalidDataException(string.Format("Compile failure.\n{0}\n{1}", compileMessage, compileErrorMessage));
            }
        }
    }
}
