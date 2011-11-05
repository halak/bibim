using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.IO;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(ColorEvalTree))]
    public sealed class ColorEvalTreeWriter : EvalTreeWriterTemplate<ColorEvalTree, Color>
    {
        public override void WriteValue(AssetStreamWriter writer, Color value)
        {
            writer.Write(value);
        }
    }
}
