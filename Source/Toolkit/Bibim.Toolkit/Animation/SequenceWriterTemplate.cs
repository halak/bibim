using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    public abstract class SequenceWriterTemplate<T, U> : GameAssetWriter<T> where T : SequenceTemplate<U>
    {
        public sealed override void Write(AssetStreamWriter writer, T asset)
        {
            int count = asset.GetNumberOfKeyframes();
            writer.Write(asset.Duration);
            writer.Write((short)count);
            for (int i = 0; i < count; i++)
            {
                var item = asset.GetKeyframe(i);
                WriteValue(writer, item.Value);
                writer.Write(item.Duration);
            }
        }

        protected abstract void WriteValue(AssetStreamWriter writer, U value);
    }
}
