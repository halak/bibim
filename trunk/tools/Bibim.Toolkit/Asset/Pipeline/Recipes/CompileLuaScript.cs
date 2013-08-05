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
            var convertedData = Utility.ConvertUsingExternalTool(@"Plugin\luac52.exe",
                                                                 args: string.Format("-o \"{1}\" \"{0}\"", input, output),
                                                                 output: output);
            return new StreamingGameAsset(convertedData);
        }
    }
}
