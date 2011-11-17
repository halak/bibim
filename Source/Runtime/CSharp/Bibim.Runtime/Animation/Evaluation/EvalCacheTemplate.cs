using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Animation
{
    public enum EvalCacheUpdateMode
    {
        UpdateAtStart,
        UpdateAtReset,
        UpdateAtEverytime,
    }

    public abstract class EvalCacheTemplate<T> : Eval<T>
    {
        #region Fields
        private T value;
        private bool valueChanged;
        #endregion

        #region Properties
        public EvalCacheUpdateMode UpdateMode
        {
            get;
            set;
        }

        public Eval<T> Source
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        protected EvalCacheTemplate()
        {
            valueChanged = true;
            UpdateMode = EvalCacheUpdateMode.UpdateAtEverytime;
        }
        #endregion

        public sealed override void Start()
        {
            if (UpdateMode == EvalCacheUpdateMode.UpdateAtStart)
                valueChanged = true;
        }

        public sealed override void Stop()
        {
        }

        public sealed override void Reset()
        {
            if (UpdateMode == EvalCacheUpdateMode.UpdateAtReset)
                valueChanged = true;
        }

        public sealed override T Evaluate(EvalContext context)
        {
            if (UpdateMode == EvalCacheUpdateMode.UpdateAtEverytime)
                valueChanged = true;

            if (valueChanged)
            {
                valueChanged = false;
                if (Source != null)
                    value = Source.Evaluate(context);
                else
                    value = default(T);
            }

            return value;
        }
    }
}
