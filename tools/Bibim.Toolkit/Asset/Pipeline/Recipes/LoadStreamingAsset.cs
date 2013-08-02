using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;

namespace Bibim.Asset.Pipeline.Recipes
{
    public sealed class LoadStreamingAsset : CookingNode<StreamingGameAsset>
    {
        #region Properties
        public string Input
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public LoadStreamingAsset()
        {
        }

        public LoadStreamingAsset(string input)
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

            byte[] buffer = null;
            using (var fs = new FileStream(input, FileMode.Open, FileAccess.Read))
            {
                BinaryReader reader = new BinaryReader(fs);
                buffer = reader.ReadBytes((int)fs.Length);
            }

            return new StreamingGameAsset(buffer);
        }
    }
}
