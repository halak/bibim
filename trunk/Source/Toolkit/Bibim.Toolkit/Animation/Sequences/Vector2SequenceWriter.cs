using System;
using Bibim.Asset;
using Bibim.IO;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(Vector2Sequence))]
    public sealed class Vector2SequenceWriter : SequenceWriterTemplate<Vector2Sequence, Vector2>
    {
        public override void WriteValue(AssetStreamWriter writer, Vector2 value)
        {
            writer.Write(value);
        }
    }
}
