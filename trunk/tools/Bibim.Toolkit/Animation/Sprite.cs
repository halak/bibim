using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using Microsoft.Xna.Framework;
using Bibim.Asset;
using Bibim.Graphics;
using Image = Bibim.Graphics.Image;

namespace Bibim.Animation
{
    [ClassID('A', 'S', 'P', 'R')]
    public sealed class Sprite : GameAsset
    {
        #region Keyframe (Nested Struct)
        public struct Keyframe
        {
            public string TextureURI;
            public Rectangle ClippingRectangle;
            public Image.Transform AppliedTransform;
            public Vector2 Origin;
            public float Duration;
        }
        #endregion

        #region Fields
        private Keyframe[] keyframes;
        private float duration;
        #endregion

        #region Properties
        public Keyframe[] Keyframes
        {
            get { return keyframes; }
        }

        public BlendMode BlendMode
        {
            get;
            set;
        }

        public bool Loop
        {
            get;
            set;
        }

        public float Duration
        {
            get { return duration; }
        }
        #endregion

        #region Constructors
        public Sprite(ICollection<Keyframe> keyframes)
        {
            this.keyframes = new Keyframe[keyframes.Count];
            keyframes.CopyTo(this.keyframes, 0);
            this.duration = 0.0f;
        }
        #endregion

        #region Methods
        #endregion
    }
}
