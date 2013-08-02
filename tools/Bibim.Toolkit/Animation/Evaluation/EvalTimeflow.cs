using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Bibim.Time;

namespace Bibim.Animation
{
    [ClassID('e', 'T', 'F', 'f')]
    public sealed class EvalTimeflow : Eval<float>, IUpdateable
    {
        #region Behavior (Nested Enum)
        public enum Behavior
        {
            Pause,
            Reset,
            Finish,
        }
        #endregion

        #region Fields
        private float evaluatedTime;
        private Timeline timeline;
        private float duration;
        private int lastTimestamp;
        private bool isUpdating;
        #endregion

        #region Properties
        public Timeline Timeline
        {
            get { return timeline; }
            set
            {
                if (timeline != value)
                {
                    if (timeline != null && isUpdating)
                        timeline.Remove(this);

                    timeline = value;

                    if (timeline != null && isUpdating)
                        timeline.Add(this);
                }
            }
        }

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

        public bool IsNormalized
        {
            get;
            set;
        }

        public Behavior StopBehavior
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public EvalTimeflow()
            : this(0.0f, 1.0f, Behavior.Pause, true, false)
        {
        }

        public EvalTimeflow(float duration)
            : this(duration, 1.0f, Behavior.Pause, true, false)
        {
        }

        public EvalTimeflow(float duration, float velocity, Behavior stopBehavior, bool isLooped, bool isNormalized)
        {
            Time = 0.0f;
            Duration = duration;
            Velocity = velocity;
            StopBehavior = stopBehavior;
            IsLooped = isLooped;
            IsNormalized = isNormalized;
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

            if (IsNormalized)
            {
                if (Duration > 0.0f)
                    evaluatedTime = Time / Duration;
                else
                    evaluatedTime = 0.0f;
            }
            else
                evaluatedTime = Time;
        }
        #endregion

        public override void Start()
        {
            if (isUpdating)
                return;

            isUpdating = true;
            if (timeline != null)
                timeline.Add(this);
        }

        public override void Stop()
        {
            if (isUpdating == false)
                return;

            isUpdating = false;
            if (timeline != null)
                timeline.Remove(this);

            switch (StopBehavior)
            {
                case Behavior.Pause:
                    break;
                case Behavior.Reset:
                    Time = 0.0f;
                    break;
                case Behavior.Finish:
                    Time = Duration;
                    break;
            }
        }

        public override void Reset()
        {
            Time = 0.0f;
            evaluatedTime = 0.0f;
        }

        public override float Evaluate(EvalContext context)
        {
            return evaluatedTime;
        }
    }
}
