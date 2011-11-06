using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Animation
{
    public abstract class EvalSequenceTemplate<T, TSequence> : EvalSequenceBaseTemplate<T> where TSequence : SequenceTemplate<T>
    {
        #region Fields
        private int timeIndex;
        #endregion

        #region Properties
        public TSequence Source
        {
            get;
            set;
        }
        #endregion

        #region Methods
        protected sealed override void UpdateValue()
        {
            if (Source == null || Source.Duration == 0.0f)
                return;

            float duration = Source.Duration;
            float clippedTime = Looped ? Time % duration : Math.Min(Time, duration);

            timeIndex = Source.GetKeyframeIndex(clippedTime, timeIndex);
            if (timeIndex < Source.GetNumberOfKeyframes() - 1)
            {
                Keyframe<T> k1 = Source.GetKeyframe(timeIndex);
                Keyframe<T> k2 = Source.GetKeyframe(timeIndex + 1);
                Value = Interpolate(k1.Value, k2.Value, (clippedTime - k1.StartTime) / k1.Duration);
            }
            else
                Value = Source.GetKeyframe(timeIndex).Value;
        }

        protected abstract T Interpolate(T a, T b, float t);
        #endregion

        #region IXmlSerializable
        public override void ReadXml(System.Xml.XmlReader reader)
        {
            throw new NotImplementedException();
        }

        public override void WriteXml(System.Xml.XmlWriter writer)
        {
            throw new NotImplementedException();
        }
        #endregion
    }
}
