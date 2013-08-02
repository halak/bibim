using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Text;
using Microsoft.Xna.Framework;
using Bibim.Graphics;
using Bibim.UI;
using Bibim.UI.Effects;
using Bibim.UI.Events;
using Bibim.UI.Visuals;
using Image = Bibim.Graphics.Image;
using Rectangle = Microsoft.Xna.Framework.Rectangle;
using GDIColor = System.Drawing.Color;

namespace Bibim.Asset.Pipeline.Recipes
{
    public class DirectoryToImageSet : CookingNode<ImageSet>
    {
        #region Properties
        public string Input
        {
            get;
            set;
        }

        public Size UniformSize
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public DirectoryToImageSet()
            : this(string.Empty, Size.Empty)
        {
        }

        public DirectoryToImageSet(string input)
            : this(input, Size.Empty)
        {
        }

        public DirectoryToImageSet(string input, Size uniformSize)
        {
            this.Input = input;
            this.UniformSize = uniformSize;
        }
        #endregion

        public override ImageSet Cook(CookingContext context)
        {
            string actualPath = Path.Combine(context.BaseDirectory, context.Directory, context.ExpandVariables(Input));

            Dictionary<string, Image> items = new Dictionary<string, Image>();
            foreach (var item in Directory.GetFiles(actualPath))
            {
                string name = Path.GetFileNameWithoutExtension(item);
                Bitmap bitmap = BitmapExtension.CreateOne(item);

                if (UniformSize.IsEmpty == false)
                    bitmap = bitmap.ResizeAndDispose(UniformSize.Width, UniformSize.Height);

                items.Add(name, new Image(string.Empty, Rectangle.Empty)
                {
                    Tag = new ImageCookingTag(bitmap)
                });
            }

            return new ImageSet(items);
        }
    }
}
