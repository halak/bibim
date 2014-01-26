using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using Bibim.GFX;
using Bibim.UI;
using Bibim.UI.Visuals;
using Image = Bibim.Graphics.Image;

namespace Bibim.Asset.Pipeline.Recipes
{
    public sealed class ExportSparkSet : ExportTemplate<SparkSet>
    {
        #region Constructors
        public ExportSparkSet()
            : base()
        {
        }

        public ExportSparkSet(CookingNode<SparkSet> input)
            : base(input)
        {
        }
        #endregion

        protected override void Export(CookingContext context, SparkSet input)
        {
            ExportImageSet.Export(context, input.Images, BitmapSheetSize, BitmapSheetClusterSize, TextureOutput);
        }
    }
}
