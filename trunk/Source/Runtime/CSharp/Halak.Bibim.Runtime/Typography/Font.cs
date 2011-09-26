using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Halak.Bibim.Asset;
using Microsoft.Xna.Framework;

namespace Halak.Bibim.Typography
{
    [GameAsset('F', 'O', 'N', 'T')]
    public sealed class Font : GameAsset
    {
        #region Fields
        private FontParameter parameters;
        private float spacing;
        private Color color;
        private Color strokeColor;
        private Color glowColor;
        #endregion

        #region Properties
        public string Face
        {
            get { return parameters.Face ; }
            set
            {
                if (parameters.Face != value)
                {
                    parameters.Face = value;
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

        public int GlowSize
        {
            get { return parameters.GlowSize; }
            set
            {
                if (parameters.GlowSize != value)
                {
                    parameters.GlowSize = value;
                    Revision++;
                }
            }
        }

        public float GlowSpread
        {
            get { return parameters.GlowSpread; }
            set
            {
                if (parameters.GlowSpread != value)
                {
                    parameters.GlowSpread = value;
                    Revision++;
                }
            }
        }

        public float GlowThickness
        {
            get { return parameters.GlowThickness; }
            set
            {
                if (parameters.GlowThickness != value)
                {
                    parameters.GlowThickness = value;
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

        public Color GlowColor
        {
            get { return glowColor; }
            set
            {
                if (glowColor != value)
                {
                    glowColor = value;
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
