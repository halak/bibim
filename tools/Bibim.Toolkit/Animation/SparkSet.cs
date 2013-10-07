using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Bibim.Asset;
using Bibim.Graphics;

namespace Bibim.Animation
{
    [ClassID('S', 'P', 'K', 'S')]
    public sealed class SparkSet : GameAsset
    {
        #region Fields
        private Dictionary<string, Spark> sparks;
        #endregion

        #region Properties
        public IDictionary<string, Spark> Sparks
        {
            get { return sparks; }
        }

        public ImageSet Images
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public SparkSet()
        {
            this.sparks = new Dictionary<string, Spark>();
            this.Images = new ImageSet();
        }

        public SparkSet(IDictionary<string, Spark> sparks)
        {
            this.sparks = new Dictionary<string, Spark>(sparks);
            this.Images = new ImageSet();
        }
        #endregion
    }
}
