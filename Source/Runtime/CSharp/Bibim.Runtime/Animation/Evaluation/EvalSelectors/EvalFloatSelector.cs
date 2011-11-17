using System;

namespace Bibim.Animation
{
    [ClassID('e', 'T', 'f', '_')]
    public sealed class EvalFloatSelector : EvalSelectorTemplate<float>
    {
        public sealed class CaseObject : CaseObjectBase { }
        public sealed class CaseObjectCollection : System.Collections.Generic.List<CaseObject>
        {
            public CaseObjectCollection() { }
            public CaseObjectCollection(int capacity) : base(capacity) { }
        }

        public CaseObjectCollection CaseObjects
        {
            get { return GetCaseObjects<CaseObject, CaseObjectCollection>(); }
            set { SetCaseObjects<CaseObject, CaseObjectCollection>(value); }
        }

        #region Constructors
        public EvalFloatSelector()
        {
        }
        #endregion
    }
}
