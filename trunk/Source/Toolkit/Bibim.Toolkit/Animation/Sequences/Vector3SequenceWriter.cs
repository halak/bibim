using System;
using Bibim.Asset;
using Bibim.IO;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(Vector3Sequence))]
    public sealed class Vector3SequenceWriter : SequenceWriterTemplate<Vector3Sequence, Vector3>
    {
        public override void WriteValue(AssetStreamWriter writer, Vector3 value)
        {
            writer.Write(value);
        }
    }
}
