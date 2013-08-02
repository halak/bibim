using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;

namespace Bibim.Graphics
{
    [ClassID('S', 'H', 'E', 'F')]
    public sealed class ShaderEffect : GameAsset
    {
        private GraphicsDevice graphicsDevice;

        public GraphicsDevice GraphicsDevice
        {
            get { return graphicsDevice; }
        }

        public ShaderEffect(GraphicsDevice graphicsDevice)
        {
            this.graphicsDevice = graphicsDevice;
        }
    }
}
