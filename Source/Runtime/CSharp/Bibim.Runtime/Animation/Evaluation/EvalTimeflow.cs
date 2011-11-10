using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 'T', 'F', 'f')]
    public sealed class EvalTimeflow : Eval<float>
    {
        #region Fields
        private float duration;
        private int lastTimestamp;
        #endregion

        #region Properties
        public float Time
        {
            get;
            private set;
        }

        public float Duration
        {
            get { return duration; }
            set
            {
                duration = Math.Max(value, 0.0f);
            }
        }

        public float Velocity
        {
            get;
            set;
        }

        public bool IsLooped
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public EvalTimeflow()
            : this(0.0f, 1.0f, true)
        {
        }

        public EvalTimeflow(float duration)
            : this(duration, 1.0f, true)
        {
        }

        public EvalTimeflow(float duration, float velocity, bool isLooped)
        {
            Time = 0.0f;
            duration = Math.Max(duration, 0.0f);
            Velocity = velocity;
            IsLooped = isLooped;
        }
        #endregion

        #region Methods
        public void Update(float dt, int timestamp)
        {
            if (lastTimestamp == timestamp || Velocity == 0.0f)
                return;
            else
                lastTimestamp = timestamp;

            float nextTime = Time + dt;

            if (0 <= nextTime && nextTime <= duration)
                Time = nextTime;
            else
            {
                if (nextTime < duration)
                {
                    if (IsLooped && duration > 0.0f)
                        Time = nextTime % duration;
                    else
                        Time = duration;
                }
                else
                {
                    if (IsLooped && duration > 0.0f)
                        Time = duration - (-nextTime % duration);
                    else
                        Time = 0.0f;
                }
            }
        }
        #endregion

        public override void Reset()
        {
            Time = 0.0f;
        }

        public override float Evaluate(EvalContext context)
        {
            return Time;
        }
    }
}
