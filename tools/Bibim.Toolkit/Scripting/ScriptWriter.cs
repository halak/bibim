﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Scripting
{
    [GameAssetWriter(typeof(Script))]
    public sealed class ScriptWriter : GameAssetWriter<Script>
    {
        public override void Write(AssetStreamWriter writer, Script asset)
        {
            writer.Write(asset.ClassID);
            writer.Write(asset.Buffer.Length);
            writer.Write(asset.Buffer);
            writer.Write(asset.FunctionTable.Length);
            foreach (Script.Function item in asset.FunctionTable)
            {
                writer.WriteBibimString(item.Name);
                writer.Write(item.Position);
                writer.Write(item.ArgumentStackSize);
                writer.Write(item.ReturnTypes.Length);
                foreach (ScriptObjectType type in item.ReturnTypes)
                    writer.Write((int)type);
                writer.Write(item.ParameterTypes.Length);
                foreach (ScriptObjectType type in item.ParameterTypes)
                    writer.Write((int)type);
            }
            writer.Write(asset.StringTable.Length);
            foreach (string item in asset.StringTable)
                writer.WriteBibimString(item);
        }
    }
}
