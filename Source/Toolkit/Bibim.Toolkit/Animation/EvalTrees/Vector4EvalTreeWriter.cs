using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.IO;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(Vector4EvalTree))]
    public sealed class Vector4EvalTreeWriter : EvalTreeWriterTemplate<Vector4EvalTree, Vector4>
    {
        public override void WriteValue(AssetStreamWriter writer, Vector4 value)
        {
            writer.Write(value);
        }
    }
}
