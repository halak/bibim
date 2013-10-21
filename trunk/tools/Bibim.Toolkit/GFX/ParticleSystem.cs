using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Bibim.Asset;
using Microsoft.Xna.Framework;

namespace Bibim.GFX
{
    [ClassID('A', 'S', 'P', 'S')]
    public sealed class ParticleSystem : GameAsset
    {
        #region Fields
        public enum EmitterMode
        {
            Gravity,
            Radius,
        }
        #endregion

        #region Properties
        public float Angle { get; set; }
        public float AngleVariance { get; set; }
        public int BlendFunctionDestination { get; set; }
        public int BlendFunctionSource { get; set; }
        public float Duration { get; set; }
        public EmitterMode Mode { get; set; }
        public Vector4 FinishColor { get; set; }
        public Vector4 FinishColorVariance { get; set; }
        public float FinishParticleRotation { get; set; }
        public float FinishParticleRotationVariance { get; set; }
        public float FinishParticleSize { get; set; }
        public float FinishParticleSizeVariance { get; set; }
        public Vector2 Gravity { get; set; }
        public int MaxParticles { get; set; }
        public float MaxRadius { get; set; }
        public float MaxRadiusVariance { get; set; }
        public float MinRadius { get; set; }
        public float MinRadiusVariance { get; set; }
        public float ParticleLifespan { get; set; }
        public float ParticleLifespanVariance { get; set; }
        public float RadialAccelVariance { get; set; }
        public float RadialAcceleration { get; set; }
        public float Spin { get; set; }
        public float SpinVariance { get; set; }
        public bool RotationIsDirection { get; set; }
        public Vector2 SourcePosition { get; set; }
        public Vector2 SourcePositionVariance { get; set; }
        public float Speed { get; set; }
        public float SpeedVariance { get; set; }
        public Vector4 StartColor { get; set; }
        public Vector4 StartColorVariance { get; set; }
        public float StartParticleRotation { get; set; }
        public float StartParticleRotationVariance { get; set; }
        public float StartParticleSize { get; set; }
        public float StartParticleSizeVariance { get; set; }
        public float TangentialAccelVariance { get; set; }
        public float TangentialAcceleration { get; set; }
        public Bibim.Graphics.Image Image { get; set; }
        #endregion

        #region Constructors
        public ParticleSystem()
        {
        }
        #endregion
    }
}
