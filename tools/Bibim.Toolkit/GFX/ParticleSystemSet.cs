using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Bibim.Asset;
using Bibim.Graphics;

namespace Bibim.GFX
{
    [ClassID('P', 'S', 'S', 'T')]
    public sealed class ParticleSystemSet : GameAsset
    {
        #region Fields
        private Dictionary<string, ParticleSystem> particleSystems;
        #endregion

        #region Properties
        public IDictionary<string, ParticleSystem> ParticleSystems
        {
            get { return particleSystems; }
        }
        #endregion

        #region Constructors
        public ParticleSystemSet()
        {
            this.particleSystems = new Dictionary<string, ParticleSystem>();
        }

        public ParticleSystemSet(IDictionary<string, ParticleSystem> particleSystems)
        {
            this.particleSystems = new Dictionary<string, ParticleSystem>(particleSystems);
        }
        #endregion
    }
}
