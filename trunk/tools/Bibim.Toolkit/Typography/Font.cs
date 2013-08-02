using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Microsoft.Xna.Framework;

namespace Bibim.Typography
{
    [ClassID('F', 'O', 'N', 'T')]
    public sealed class Font : GameAsset
    {
        #region Fields
        private FontCacheParameter parameters;
        private Vector2 shadowOffset;
        private float spacing;
        private Color color;
        private Color strokeColor;
        private Color shadowColor;
        #endregion

        #region Properties
        public FontLibrary Library
        {
            get;
            set;
        }

        public string FaceURI
        {
            get { return parameters.FaceURI ; }
            set
            {
                if (parameters.FaceURI != value)
                {
                    parameters.FaceURI = value;
                    Revision++;
                }
            }
        }

        public float FontSize
        {
            get { return parameters.FontSize; }
            set
            {
                if (parameters.FontSize != value)
                {
                    parameters.FontSize = value;
                    Revision++;
                }
            }
        }

        public float StrokeSize
        {
            get { return StrokeSize; }
            set
            {
                if (StrokeSize != value)
                {
                    StrokeSize = value;
                    Revision++;
                }
            }
        }

        public float Weights
        {
            get { return parameters.Weights; }
            set
            {
                if (parameters.Weights != value)
                {
                    parameters.Weights = value;
                    Revision++;
                }
            }
        }

        public float Shear
        {
            get { return parameters.Shear; }
            set
            {
                if (parameters.Shear != value)
                {
                    parameters.Shear = value;
                    Revision++;
                }
            }
        }

        public int ShadowSize
        {
            get { return parameters.ShadowSize; }
            set
            {
                if (parameters.ShadowSize != value)
                {
                    parameters.ShadowSize = value;
                    Revision++;
                }
            }
        }

        public float ShadowSpread
        {
            get { return parameters.ShadowSpread; }
            set
            {
                if (parameters.ShadowSpread != value)
                {
                    parameters.ShadowSpread = value;
                    Revision++;
                }
            }
        }

        public float ShadowThickness
        {
            get { return parameters.ShadowThickness; }
            set
            {
                if (parameters.ShadowThickness != value)
                {
                    parameters.ShadowThickness = value;
                    Revision++;
                }
            }
        }

        public Vector2 ShadowOffset
        {
            get { return shadowOffset; }
            set
            {
                if (shadowOffset != value)
                {
                    shadowOffset = value;
                    Revision++;
                }
            }
        }

        public float Scale
        {
            get { return parameters.Scale; }
            set
            {
                if (parameters.Scale != value)
                {
                    parameters.Scale = value;
                    Revision++;
                }
            }
        }

        public bool Hinting
        {
            get { return parameters.Hinting; }
            set
            {
                if (parameters.Hinting != value)
                {
                    parameters.Hinting = value;
                    Revision++;
                }
            }
        }

        public bool IgnoreBitmap
        {
            get { return parameters.IgnoreBitmap; }
            set
            {
                if (parameters.IgnoreBitmap != value)
                {
                    parameters.IgnoreBitmap = value;
                    Revision++;
                }
            }
        }

        public float Spacing
        {
            get { return spacing; }
            set
            {
                if (spacing != value)
                {
                    spacing = value;
                    Revision++;
                }
            }
        }

        public Color Color
        {
            get { return color; }
            set
            {
                if (color != value)
                {
                    color = value;
                    Revision++;
                }
            }
        }

        public Color StrokeColor
        {
            get { return strokeColor; }
            set
            {
                if (strokeColor != value)
                {
                    strokeColor = value;
                    Revision++;
                }
            }
        }

        public Color ShadowColor
        {
            get { return shadowColor; }
            set
            {
                if (shadowColor != value)
                {
                    shadowColor = value;
                    Revision++;
                }
            }
        }
        #endregion

        #region Constructors
        public Font()
        {
        }
        #endregion
    }
}
