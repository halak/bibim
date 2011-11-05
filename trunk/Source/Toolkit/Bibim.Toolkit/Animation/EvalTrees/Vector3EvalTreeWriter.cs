using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.IO;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(Vector3EvalTree))]
    public sealed class Vector3EvalTreeWriter : EvalTreeWriterTemplate<Vector3EvalTree, Vector3>
    {
        public override void WriteValue(AssetStreamWriter writer, Vector3 value)
        {
            writer.Write(value);
        }
    }
}
