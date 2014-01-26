using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using Bibim.Graphics;
using Bibim.UI;
using Bibim.UI.Visuals;
using Image = Bibim.Graphics.Image;

namespace Bibim.Asset.Pipeline.Recipes
{
    public abstract class ExportTemplate<T> : CookingNode<T> where T : GameAsset
    {
        #region Fields
        private string textureOutput;
        #endregion

        #region Properties
        public CookingNode<T> Input
        {
            get;
            set;
        }

        public Size BitmapSheetSize
        {
            get;
            set;
        }

        public Size BitmapSheetClusterSize
        {
            get;
            set;
        }

        public string TextureOutput
        {
            get { return textureOutput; }
            set
            {
                textureOutput = value ?? string.Empty;
            }
        }
        #endregion

        #region Constructors
        public ExportTemplate()
            : this(null)
        {
        }

        public ExportTemplate(CookingNode<T> input)
        {
            Input = input;
            BitmapSheetSize = new Size(1024, 1024);
            BitmapSheetClusterSize = new Size(16, 16);
            textureOutput = "$(AssetName)_TEX{0}";
        }
        #endregion

        public sealed override T Cook(CookingContext context)
        {
            if (BitmapSheetSize.IsEmpty)
                throw new InvalidOperationException("BitmapSheetSize is empty.");
            if (string.IsNullOrEmpty(TextureOutput))
                throw new InvalidOperationException("TextureOutput is null.");
            if (TextureOutput.Contains("{0}") == false)
                throw new InvalidOperationException("TextureOutput not exists {0}.");

            var input = Input.Cook(context);

            Export(context, input);

            return input;
        }

        protected abstract void Export(CookingContext context, T input);
    }
}
