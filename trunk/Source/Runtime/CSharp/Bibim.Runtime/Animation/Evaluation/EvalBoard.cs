using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Bibim.Asset;

namespace Bibim.Animation
{
    [ClassID('e', 'b', 'o', 'd')]
    public sealed class EvalBoard : GameAsset
    {
        #region Item (Nested Struct)
        public struct Item
        {
            public string Name;
            public EvalBase Root;

            public Item(string name, EvalBase root)
            {
                Name = name ?? string.Empty;
                Root = root;
            }
        }

        public sealed class ItemCollection : List<Item>
        {
        }
        #endregion

        #region Fields
        private float duration;
        #endregion

        #region Properties
        public float Duration
        {
            get { return duration; }
            set
            {
                duration = Math.Max(value, 0.0f);
            }
        }

        public ItemCollection Items
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public EvalBoard()
        {
            Items = new ItemCollection();
            duration = 0.0f;
        }
        #endregion
    }
}
