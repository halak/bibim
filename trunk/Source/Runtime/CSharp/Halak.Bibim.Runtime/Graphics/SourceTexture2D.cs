using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;

namespace Bibim.Graphics
{
    [ClassID('S', 'T', 'X', '2')]
    public sealed class SourceTexture2D : Texture2D
    {
        public SourceTexture2D()
        {
        }

        public SourceTexture2D(GraphicsDevice graphicsDeivce, int width, int height, int surfaceWidth, int surfaceHeight)
            : base(graphicsDeivce)
        {
            Setup(width, height, surfaceWidth, surfaceHeight);
        }

        public class Reader : GameAssetReader<SourceTexture2D>
        {
            public override SourceTexture2D Read(AssetStreamReader reader, SourceTexture2D existingInstance)
            {
                throw new NotImplementedException();
            }
        }
    }
}
