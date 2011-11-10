using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Animation
{
    public struct Keyframe<T>
    {
        public static readonly Keyframe<T> Empty = new Keyframe<T>();
        public static readonly Keyframe<T>[] ZeroArray = new Keyframe<T>[0] { };

        public T Value;
        public float Duration;
        public float StartTime;

        public Keyframe(T value, float duration)
        {
            Value = value;
            Duration = duration;
            StartTime = 0.0f;
        }

        public Keyframe(T value, float duration, float startTime)
        {
            Value = value;
            Duration = duration;
            StartTime = startTime;
        }
    }
}
