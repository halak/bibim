using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Animation
{
    public abstract class EvalSequenceBaseTemplate<T> : Eval<T>
    {
        #region Fields
        private uint lastTimestamp;
        private bool timeChanged;
        #endregion

        #region Properties
        public float Time
        {
            get;
            private set;
        }

        public float Velocity
        {
            get;
            set;
        }

        public bool Looped
        {
            get;
            set;
        }

        protected T Value
        {
            private get;
            set;
        }
        #endregion

        #region Constructors
        public EvalSequenceBaseTemplate()
        {
            Time = 0.0f;
            Velocity = 1.0f;
            Looped = false;
            timeChanged = true;
            lastTimestamp = 0;
        }
        #endregion

        #region Methods
        public void Update(float dt, uint timestamp)
        {
            if (lastTimestamp == timestamp)
                return;
            else
                lastTimestamp = timestamp;

            Time += dt;
            timeChanged = true;
        }

        public sealed override void Start()
        {
            Reset();
        }

        public sealed override void Stop()
        {
        }

        public sealed override void Reset()
        {
            Time = 0.0f;
            timeChanged = true;
        }

        public sealed override T Evaluate(EvalContext context)
        {
            if (timeChanged)
            {
                timeChanged = false;
                UpdateValue();
            }

            return Value;
        }

        protected abstract void UpdateValue();
        #endregion
    }
}
