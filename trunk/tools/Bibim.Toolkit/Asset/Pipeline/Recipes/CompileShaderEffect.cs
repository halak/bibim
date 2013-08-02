using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;
using Bibim.Collections.Generic;
using Bibim.Graphics;

namespace Bibim.Asset.Pipeline.Recipes
{
    public abstract class CompileShaderEffect : CookingNode<ShaderEffect>
    {
        #region Fields
        private Dictionary<string, string> defines;
        #endregion

        #region Properties
        public string Input
        {
            get;
            set;
        }

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

        public sealed override ShaderEffect Cook(CookingContext context)
        {
            string assetPath = Path.Combine(context.Directory, context.ExpandVariables(Input));
            string input = Path.Combine(context.BaseDirectory, assetPath);
            if (File.Exists(input) == false)
                throw new FileNotFoundException(string.Empty, input);

            context.AddDependency(input);

            List<string> codeLines = new List<string>();
            using (var inputStream = new FileStream(input, FileMode.Open, FileAccess.Read))
            {
                var reader = new StreamReader(inputStream);
                while (reader.EndOfStream == false)
                    codeLines.Add(reader.ReadLine());
            }

            string code = Preprocess(defines, codeLines);
            var result = Compile(code);
            var byteCode = result.Item1;
            var extra = result.Item2;

            return new ShaderEffect(null)
            {
                Tag = new ShaderEffectCookingTag(byteCode, extra)
            };
        }

        protected abstract string Preprocess(Dictionary<string, string> defines, IList<string> codeLines);
        protected abstract Tuple<byte[], int> Compile(string code);
    }
}
