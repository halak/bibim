using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using XnaGraphicsDevice = Microsoft.Xna.Framework.Graphics.GraphicsDevice;

namespace Bibim.Graphics
{
    [ClassID('G', 'R', 'P', 'D')]
    public sealed class GraphicsDevice : GameModule
    {
        XnaGraphicsDevice g;

        public GraphicsDevice(XnaGraphicsDevice g)
        {
            this.g = g;
        }
    }
}
