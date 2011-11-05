using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    public abstract class EvalRangedSequenceTemplate<T, TSequence> : EvalSequenceBaseTemplate<T> where TSequence : SequenceTemplate<T>
    {
        #region Fields
        private int timeIndex1;
        private int timeIndex2;
        #endregion

        #region Properties
        public TSequence Source1
        {
            get;
            set;
        }

        public TSequence Source2
        {
            get;
            set;
        }
        #endregion

        #region Methods
        protected sealed override void UpdateValue()
        {
            if (Source1 == null || Source2 == null)
                return;

            float duration1 = Source1.Duration;
            if (duration1 == 0.0f)
                return;

            float duration2 = Source2.Duration;
            if (duration2 == 0.0f)
                return;
           
            float clippedTime1 = Looped ? Time % duration1 : Math.Min(Time, duration1);
            float clippedTime2 = Looped ? Time % duration2 : Math.Min(Time, duration2);

            timeIndex1 = Source1.GetKeyframeIndex(clippedTime1, timeIndex1);
            timeIndex2 = Source2.GetKeyframeIndex(clippedTime2, timeIndex2);
            if (timeIndex1 < Source1.GetNumberOfKeyframes() - 1)
            {
                Keyframe<T> k1 = Source1.GetKeyframe(timeIndex1);
                Keyframe<T> k2 = Source1.GetKeyframe(timeIndex1 + 1);
                Value = Interpolate(k1.Value, k2.Value, (clippedTime1 - k1.StartTime) / k1.Duration);
            }
            else
                Value = Source1.GetKeyframe(timeIndex1).Value;
        }

        protected abstract T Interpolate(T a, T b, float t);
        #endregion
    }
}
