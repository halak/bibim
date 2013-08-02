using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 'U', 'R', 'f')]
    public sealed class EvalUnitRandom : Eval<float>
    {
        #region Fields
        private int initialSeed;
        private Random random;
        #endregion

        #region Properties
        public int InitialSeed
        {
            get { return initialSeed; }
            set
            {
                value = Math.Max(value, 0);
                if (initialSeed != value)
                {
                    initialSeed = value;
                    if (initialSeed != 0)
                        random = new Random(initialSeed);
                    else
                        random = new Random();
                }
            }
        }
        #endregion

        #region Constructors
        public EvalUnitRandom()
        {
            initialSeed = 0;
            random = new Random();
        }
        #endregion

        public override void Start() { }
        public override void Stop() { }
        public override void Reset() { }

        public override float Evaluate(EvalContext context)
        {
            int generatedValue = random.Next(10000);
            float value = ((float)generatedValue) * 0.0001f;
            return value;
        }
    }
}
