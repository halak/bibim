using System;
using Bibim.Asset;
using Bibim.IO;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(Vector4Sequence))]
    public sealed class Vector4SequenceWriter : SequenceWriterTemplate<Vector4Sequence, Vector4>
    {
        public override void WriteValue(AssetStreamWriter writer, Vector4 value)
        {
            writer.Write(value);
        }
    }
}
