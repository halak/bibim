﻿using System;
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
            writer.Write(asset.FunctionTable.Length);
            foreach (Script.Function item in asset.FunctionTable)
            {
                writer.WriteBibimString(item.Name);
                writer.Write(item.Position);
                writer.Write(item.ArgumentStackSize);
                writer.Write((int)item.ReturnType);
                writer.Write(item.ParameterTypes.Length);
                foreach (ScriptObjectType parameterType in item.ParameterTypes)
                    writer.Write((int)parameterType);
            }
            writer.Write(asset.StringTable.Count);
            foreach (string item in asset.StringTable)
                writer.WriteBibimString(item);
        }
    }
}
