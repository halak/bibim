using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    public abstract class EvalInterpolatorTemplate<T> : Eval<T>
    {
        #region Fields
        private EasingCurve easingCurve;
        #endregion

        #region Properties
        public Eval<T> Value1
        {
            get;
            set;
        }

        public Eval<T> Value2
        {
            get;
            set;
        }

        public Eval<float> Weight
        {
            get;
            set;
        }

        public EasingCurve EasingCurve
        {
            get { return easingCurve; }
            set
            {
                easingCurve = value ?? EaseInOutQuadraticCurve.Instance;
            }
        }
        #endregion

        public sealed override void Start()
        {
            if (Value1 != null)
                Value1.Start();
            if (Value2 != null)
                Value2.Start();
            if (Weight != null)
                Weight.Start();
        }

        public sealed override void Stop()
        {
            if (Value1 != null)
                Value1.Stop();
            if (Value2 != null)
                Value2.Stop();
            if (Weight != null)
                Weight.Stop();
        }

        public sealed override void Reset()
        {
            if (Value1 != null)
                Value1.Reset();
            if (Value2 != null)
                Value2.Reset();
            if (Weight != null)
                Weight.Reset();
        }

        public sealed override T Evaluate(EvalContext context)
        {
            if (Value1 != null && Value2 != null && Weight != null)
                return Interpolate(Value1.Evaluate(context),
                                   Value2.Evaluate(context),
                                   easingCurve.Ease(Weight.Evaluate(context)));
            else
                return default(T);
        }

        public abstract T Interpolate(T a, T b, float t);
    }
}
