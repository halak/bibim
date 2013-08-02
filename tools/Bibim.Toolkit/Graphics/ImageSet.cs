using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Bibim.Asset;

namespace Bibim.Graphics
{
    [ClassID('I', 'M', 'G', 'S')]
    public sealed class ImageSet : GameAsset
    {
        #region Fields
        private Dictionary<string, Image> images;
        #endregion

        #region Properties
        public IDictionary<string, Image> Images
        {
            get { return images; }
        }
        #endregion

        #region Constructors
        public ImageSet()
        {
            this.images = new Dictionary<string, Image>();
        }

        public ImageSet(IDictionary<string, Image> images)
        {
            this.images = new Dictionary<string, Image>(images);
        }
        #endregion

        #region Methods
        #endregion
    }
}
