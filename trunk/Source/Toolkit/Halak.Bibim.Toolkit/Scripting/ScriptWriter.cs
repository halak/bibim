using System;
using System.Collections.Generic;
using System.Text;
using Halak.Bibim.Asset;

namespace Halak.Bibim.Scripting
{
    [GameAssetWriter(typeof(Script))]
    public sealed class ScriptWriter : GameAssetWriter<Script>
    {
        public override void Write(AssetStreamWriter writer, Script asset)
        {
            writer.Write(asset.ClassID);
            writer.Write(asset.Buffer);
            writer.Write(asset.EntryPoint);
        }
    }
}
