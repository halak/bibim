using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Text;

namespace Bibim.Graphics
{
    [Serializable]
    //[DebuggerVisualizer(typeof(ImageCookingTagDebuggerVisualizer))]
    public sealed class SpriteCookingTag
    {
        #region Properties
        public List<Bitmap> Bitmaps
        {
            get;
            private set;
        }
        #endregion

        #region Constructors
        public SpriteCookingTag()
        {
        }

        public SpriteCookingTag(ICollection<Bitmap> bitmap)
        {
            Bitmaps = new List<Bitmap>(bitmap);
        }
        #endregion
    }
}
