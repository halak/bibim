using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    public abstract class EvalTreeWriterTemplate<T, U> : GameAssetWriter<T> where T : EvalTreeTemplate<U>
    {
        public override void Write(AssetStreamWriter writer, T asset)
        {
            writer.Write(asset.ClassID);
            WriteComponent(writer, asset.Root);
        }

        public void WriteComponent(AssetStreamWriter writer, Eval<U> o)
        {
        }

        public abstract void WriteValue(AssetStreamWriter writer, U value);
    }
}
