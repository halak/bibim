using System;
using Bibim.Asset;
using Bibim.IO;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(ColorSequence))]
    public sealed class ColorSequenceWriter : SequenceWriterTemplate<ColorSequence, Color>
    {
        public override void WriteValue(AssetStreamWriter writer, Color value)
        {
            writer.Write(value);
        }
    }
}
