using System;
using System.Collections.Generic;
using System.Text;
using Halak.Bibim.Asset;
using Halak.Bibim.IO;

namespace Halak.Bibim.Scripting
{
    [GameAssetWriter(typeof(Script))]
    public sealed class ScriptWriter : GameAssetWriter<Script>
    {
        public override void Write(AssetStreamWriter writer, Script asset)
        {
            writer.Write(asset.ClassID);
            writer.Write(asset.Buffer.Length);
            writer.Write(asset.Buffer);
            writer.Write(asset.EntryPoint);
            writer.Write(asset.StringTable.Count);
            foreach (string item in asset.StringTable)
                writer.WriteBibimString(item);
        }
    }
}
