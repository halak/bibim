using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.Asset.Pipeline;
using Bibim.IO;
using Bibim.Graphics;

namespace Bibim.GFX
{
    [GameAssetWriter(typeof(ParticleSystemSet))]
    public sealed class ParticleSystemSetWriter : GameAssetWriter<ParticleSystemSet>
    {
        public override void Write(AssetStreamWriter writer, ParticleSystemSet asset)
        {
            writer.Write(asset.ClassID);
            writer.Write((short)asset.ParticleSystems.Count);
            foreach (var item in asset.ParticleSystems)
            {
                writer.WriteBibimString(item.Key);
                ParticleSystemWriter.WriteBody(writer, item.Value);
            }
        }
    }
}
