using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.Asset.Pipeline;
using Bibim.IO;
using Bibim.Graphics;

namespace Bibim.GFX
{
    [GameAssetWriter(typeof(ParticleSystem))]
    public sealed class ParticleSystemWriter : GameAssetWriter<ParticleSystem>
    {
        public override void Write(AssetStreamWriter writer, ParticleSystem asset)
        {
            writer.Write(asset.ClassID);
            WriteBody(writer, asset);
        }

        public static void WriteBody(AssetStreamWriter writer, ParticleSystem asset)
        {
            writer.Write(asset.Angle);
            writer.Write(asset.AngleVariance);
            writer.Write(asset.BlendFunctionDestination);
            writer.Write(asset.BlendFunctionSource);
            writer.Write(asset.Duration);
            writer.Write((byte)asset.Mode);
            writer.Write(asset.FinishColor);
            writer.Write(asset.FinishColorVariance);
            writer.Write(asset.FinishParticleRotation);
            writer.Write(asset.FinishParticleRotationVariance);
            writer.Write(asset.FinishParticleSize);
            writer.Write(asset.FinishParticleSizeVariance);
            writer.Write(asset.Gravity);
            writer.Write(asset.MaxParticles);
            writer.Write(asset.MaxRadius);
            writer.Write(asset.MaxRadiusVariance);
            writer.Write(asset.MinRadius);
            writer.Write(asset.MinRadiusVariance);
            writer.Write(asset.ParticleLifespan);
            writer.Write(asset.ParticleLifespanVariance);
            writer.Write(asset.RadialAccelVariance);
            writer.Write(asset.RadialAcceleration);
            writer.Write(asset.Spin);
            writer.Write(asset.SpinVariance);
            writer.Write(asset.RotationIsDirection);
            writer.Write(asset.SourcePosition);
            writer.Write(asset.SourcePositionVariance);
            writer.Write(asset.Speed);
            writer.Write(asset.SpeedVariance);
            writer.Write(asset.StartColor);
            writer.Write(asset.StartColorVariance);
            writer.Write(asset.StartParticleRotation);
            writer.Write(asset.StartParticleRotationVariance);
            writer.Write(asset.StartParticleSize);
            writer.Write(asset.StartParticleSizeVariance);
            writer.Write(asset.TangentialAccelVariance);
            writer.Write(asset.TangentialAcceleration);
            ImageWriter.WriteBody(writer, asset.Image);
        }
    }
}
