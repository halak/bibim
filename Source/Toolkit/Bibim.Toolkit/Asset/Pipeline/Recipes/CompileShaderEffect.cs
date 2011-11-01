using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using Bibim.Collections.Generic;
using Bibim.Graphics;

namespace Bibim.Asset.Pipeline.Recipes
{
    public sealed class CompileShaderEffect : CookingNode<ShaderEffect>
    {
        #region Fields
        private Dictionary<string, string> defines;
        #endregion

        #region Properties
        [XmlAttribute]
        public string Input
        {
            get;
            set;
        }

        [XmlAttribute]
        public string Defines
        {
            get
            {
                if (defines != null && defines.Count > 0)
                {
                    StringBuilder builder = new StringBuilder();
                    foreach (var item in defines)
                    {
                        if (builder.Length > 0)
                            builder.Append(';');

                        if (string.IsNullOrEmpty(item.Value))
                            builder.Append(item.Key);
                        else
                            builder.AppendFormat("{0}={1}", item.Key, item.Value);
                    }

                    return builder.ToString();
                }
                else
                    return string.Empty;
            }

            set
            {
                if (string.IsNullOrEmpty(value))
                {
                    if (defines != null)
                        defines.Clear();

                    return;
                }

                string[] items = value.Split(';');

                defines = defines ?? new Dictionary<string, string>(items.Length);
                defines.Clear();

                foreach (var item in items)
                {
                    int index = item.IndexOf('=');
                    if (index != -1)
                        defines[item.Substring(0, index).Trim()] = item.Substring(index + 1).Trim();
                    else
                        defines[item.Trim()] = null;
                }
            }
        }
        #endregion

        #region Constructor
        public CompileShaderEffect()
            : this(string.Empty, null)
        {
        }

        public CompileShaderEffect(string input)
            : this(input, null)
        {
        }

        public CompileShaderEffect(string input, string defines)
        {
            this.Input = input ?? string.Empty;
            this.Defines = defines;
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
            StringBuilder definesArguments = new StringBuilder();
            foreach (var item in defines)
            {
                if (string.IsNullOrEmpty(item.Value))
                    definesArguments.AppendFormat("/D {0} ", item.Key);
                else
                    definesArguments.AppendFormat("/D {0}={1} ", item.Key, item.Value);
            }

            string args = string.Format("/T fx_2_0 /Fo \"{1}\" {2} /Zi /nologo \"{0}\"", input, outputFXOFileName, definesArguments.ToString());

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
