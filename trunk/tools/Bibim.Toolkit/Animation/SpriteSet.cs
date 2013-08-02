using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Bibim.Asset;

namespace Bibim.Animation
{
    [ClassID('S', 'P', 'R', 'S')]
    public sealed class SpriteSet : GameAsset
    {
        #region Fields
        private Dictionary<string, Sprite> sprites;
        #endregion

        #region Properties
        public IDictionary<string, Sprite> Sprites
        {
            get { return sprites; }
        }
        #endregion

        #region Constructors
        public SpriteSet()
        {
            this.sprites = new Dictionary<string, Sprite>();
        }

        public SpriteSet(IDictionary<string, Sprite> sprites)
        {
            this.sprites = new Dictionary<string, Sprite>(sprites);
        }
        #endregion

        #region Methods
        #endregion
    }
}
