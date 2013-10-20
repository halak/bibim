using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using Bibim.GFX;
using Bibim.Graphics;
using Bibim.UI;
using Bibim.UI.Visuals;
using Image = Bibim.Graphics.Image;
using Rectangle = Microsoft.Xna.Framework.Rectangle;

namespace Bibim.Asset.Pipeline.Recipes
{
    public sealed class ExportParticleSystemSet : ExportTemplate<ParticleSystemSet>
    {
        #region Constructors
        public ExportParticleSystemSet()
            : base()
        {
        }

        public ExportParticleSystemSet(CookingNode<ParticleSystemSet> input)
            : base(input)
        {
        }
        #endregion

        protected override void Export(CookingContext context, ParticleSystemSet input)
        {
            var particleBitmaps = new Dictionary<Bitmap, ParticleSystem>();
            foreach (var item in input.ParticleSystems)
            {
                var tag = (ImageCookingTag)item.Value.Image.Tag;
                particleBitmaps.Add(tag.Bitmap, item.Value);
            }

            using (var bitmapSheet = BitmapSheet.Create(particleBitmaps.Keys,
                                                        BitmapSheetSize.Width, BitmapSheetSize.Height,
                                                        BitmapSheetClusterSize.Width, BitmapSheetClusterSize.Height,
                                                        BitmapSheet.Options.PowerOfTwoSize | BitmapSheet.Options.RotatableMerging))
            {
                ExportImageSet.SaveTextureAssets(context, bitmapSheet, TextureOutput, (source, textureURI, clippingRectangle, appliedTransform) =>
                {
                    ParticleSystem value = null;
                    if (particleBitmaps.TryGetValue(source, out value))
                    {
                        value.Image.TextureURI = textureURI;
                        value.Image.ClippingRectangle = clippingRectangle;
                        value.Image.AppliedTransform = appliedTransform;
                    }
                });
            }
        }
    }
}
