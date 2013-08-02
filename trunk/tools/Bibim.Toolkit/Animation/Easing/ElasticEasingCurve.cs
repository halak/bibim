using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    public abstract class ElasticEasingCurve : EasingCurve
    {
        #region Fields
        private float amplitude;
        private float period;
        #endregion

        #region Properties
        public float Amplitude
        {
            get { return amplitude; }
            set
            {
                amplitude = value;
            }
        }

        public float Period
        {
            get { return period; }
            set
            {
                period = value;
            }
        }
        #endregion

        #region Constructors
        protected ElasticEasingCurve()
            : this(1.0f, 0.3f)
        {
        }

        protected ElasticEasingCurve(float amplitude, float period)
        {
            Amplitude = amplitude;
            Period = period;
        }
        #endregion
    }

    [ClassID('E', 'C', 'I', 'E')]
    public sealed class EaseInElasticCurve : ElasticEasingCurve
    {
        #region Constructors
        public EaseInElasticCurve()
        {
        }

        public EaseInElasticCurve(float amplitude, float period)
            : base(amplitude, period)
        {
        }
        #endregion

        public override float Ease(float t)
        {
            return Bibim.Animation.Ease.InElastic(t, Amplitude, Period);
        }
    }

    [ClassID('E', 'C', 'O', 'E')]
    public sealed class EaseOutElasticCurve : ElasticEasingCurve
    {
        #region Constructors
        public EaseOutElasticCurve()
        {
        }

        public EaseOutElasticCurve(float amplitude, float period)
            : base(amplitude, period)
        {
        }
        #endregion

        public override float Ease(float t)
        {
            return Bibim.Animation.Ease.OutElastic(t, Amplitude, Period);
        }
    }

    [ClassID('E', 'C', 'D', 'E')]
    public sealed class EaseInOutElasticCurve : ElasticEasingCurve
    {
        #region Constructors
        public EaseInOutElasticCurve()
        {
        }

        public EaseInOutElasticCurve(float amplitude, float period)
            : base(amplitude, period)
        {
        }
        #endregion

        public override float Ease(float t)
        {
            return Bibim.Animation.Ease.InOutElastic(t, Amplitude, Period);
        }
    }
}
