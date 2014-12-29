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
            var byteCode = Utility.ConvertUsingExternalTool(
                @"Plugin\luac52.exe",
                args: string.Format("-o \"{1}\" \"{0}\"", input, output),
                output: output);
            var textCode = File.ReadAllBytes(input);
            for (int i = 0; i < textCode.Length; i++)
                textCode[i] ^= 0xA8;

            using (var stream = new MemoryStream(byteCode.Length + textCode.Length + 16))
            using (var writer = new BinaryWriter(stream))
            {
                writer.Write(byteCode.Length);
                writer.Write(textCode.Length);
                writer.Write(byteCode);
                writer.Write(textCode);

                var buffer = new byte[stream.Length];
                Buffer.BlockCopy(stream.GetBuffer(), 0, buffer, 0, buffer.Length);
                return new StreamingGameAsset(buffer);
            }
        }
    }
}
