using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 'U', 'R', 'f')]
    public sealed class EvalUnitRandom : Eval<float>
    {
        #region GenerationCycle (Nested Enum)
        public enum GenerationCycle
        {
            FullManual,
            ResetOrManual,
            EachTime,
        }
        #endregion

        #region Fields
        private float value;
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
                    Generate();
                }
            }
        }

        public GenerationCycle Cycle
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public EvalUnitRandom()
            : this(GenerationCycle.EachTime)
        {
        }

        public EvalUnitRandom(GenerationCycle cycle)
        {
            value = 0.0f;
            Cycle = cycle;
            initialSeed = 0;
            random = new Random();
            Generate();
        }
        #endregion

        public void Generate()
        {
            int generatedValue = random.Next(10000);
            value = ((float)generatedValue) * 0.0001f;
        }

        public override void Start()
        {
            Reset();
        }

        public override void Stop()
        {
        }

        public override void Reset()
        {
            if (Cycle == GenerationCycle.ResetOrManual)
                Generate();
        }

        public override float Evaluate(EvalContext context)
        {
            if (Cycle == GenerationCycle.EachTime)
                Generate();

            return value;
        }
    }
}
