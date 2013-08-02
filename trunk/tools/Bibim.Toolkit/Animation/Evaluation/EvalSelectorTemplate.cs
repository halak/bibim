using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    public abstract class EvalSelectorTemplate<T> : Eval<T>
    {
        #region Case (Nested Struct)
        public struct Case
        {
            public float Min;
            public float Max;
            public Eval<T> Item;

            public Case(float min, float max, Eval<T> item)
            {
                Min = min;
                Max = max;
                Item = item;
            }
        }

        public sealed class CaseCollection : List<Case>
        {
            public CaseCollection()
            {
            }

            public CaseCollection(int capacity)
                : base(capacity)
            {
            }
        }
        #endregion

        #region CaseObject (Protected Nested Class)
        public abstract class CaseObjectBase
        {
            public float Min;
            public float Max;
            public Eval<T> Item;
        }
        #endregion

        #region Properties
        public Eval<float> Condition
        {
            get;
            set;
        }

        [System.Xml.Serialization.XmlIgnore]
        public CaseCollection Cases
        {
            get;
            set;
        }

        public Eval<T> DefaultCase
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        protected EvalSelectorTemplate()
        {
        }
        #endregion

        public sealed override void Start()
        {
            if (Condition != null)
                Condition.Start();
            
            if (Cases != null)
            {
                foreach (var item in Cases)
                {
                    if (item.Item != null)
                        item.Item.Start();
                }
            }

            if (DefaultCase != null)
                DefaultCase.Start();
        }

        public sealed override void Stop()
        {
            if (Condition != null)
                Condition.Stop();

            if (Cases != null)
            {
                foreach (var item in Cases)
                {
                    if (item.Item != null)
                        item.Item.Stop();
                }
            }

            if (DefaultCase != null)
                DefaultCase.Stop();
        }

        public sealed override void Reset()
        {
            if (Condition != null)
                Condition.Reset();

            if (Cases != null)
            {
                foreach (var item in Cases)
                {
                    if (item.Item != null)
                        item.Item.Reset();
                }
            }

            if (DefaultCase != null)
                DefaultCase.Reset();
        }

        public sealed override T Evaluate(EvalContext context)
        {
            if (Condition != null && Cases != null)
            {
                float conditionValue = Condition.Evaluate(context);

                foreach (var item in Cases)
                {
                    if (item.Min <= conditionValue && conditionValue <= item.Max)
                    {
                        if (item.Item != null)
                            return item.Item.Evaluate(context);
                        else
                            return default(T);
                    }
                }

                if (DefaultCase != null)
                    DefaultCase.Evaluate(context);
            }

            return default(T);
        }

        #region Protected Methods
        protected TCollection GetCaseObjects<TCase, TCollection>()
            where TCase : CaseObjectBase, new()
            where TCollection : List<TCase>, new()
        {
            var result = new TCollection();
            foreach (var item in Cases)
            {
                var itemObject = new TCase();
                itemObject.Min = item.Min;
                itemObject.Max = item.Max;
                itemObject.Item = item.Item;
                result.Add(itemObject);
            }

            return result;
        }

        protected void SetCaseObjects<TCase, TCollection>(TCollection value)
            where TCase : CaseObjectBase
            where TCollection : List<TCase>
        {
            if (value != null)
            {
                var result = new CaseCollection(value.Count);
                foreach (var itemObject in value)
                {
                    var item = new Case();
                    item.Min = itemObject.Min;
                    item.Max = itemObject.Max;
                    item.Item = itemObject.Item;
                    result.Add(item);
                }

                Cases = result;
            }
            else
                Cases = null;
        }
        #endregion
    }
}
