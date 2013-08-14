using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;

namespace Bibim.Graphics
{
    [ClassID('G', 'R', 'P', 'D')]
    public sealed class GraphicsDevice : GameModule
    {
        object g;

        public GraphicsDevice(object g)
        {
            this.g = g;
        }
    }
}
