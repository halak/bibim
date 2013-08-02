using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Text;
using Microsoft.Xna.Framework;

namespace Bibim.UI.Visuals
{
    [ClassID('U', 'P', 'N', 'L')]
    public class UIPanel : UIVisual
    {
        #region Fields
        private List<UIVisual> children;
        private ReadOnlyCollection<UIVisual> readonlyChildren;
        #endregion

        #region Properties
        public IList<UIVisual> Children
        {
            get { return readonlyChildren; }
        }
        #endregion

        #region Constructors
        public UIPanel()
        {
            children = new List<UIVisual>();
            readonlyChildren = new ReadOnlyCollection<UIVisual>(children);
        }
        #endregion

        #region Methods
        protected void Add(UIVisual item)
        {
            if (item == null)
                return;

            int zOrder = item.ZOrder;
            for (int i = children.Count - 1; i >= 0; i--)
            {
                if (zOrder >= children[i].ZOrder)
                {
                    Insert(i + 1, item);
                    return;
                }
            }

            Insert(0, item);
        }

        private void Insert(int index, UIVisual item)
        {
            index = MathExtension.Clamp(index, 0, children.Count);

            if (item.Parent != null)
                item.Parent.Remove(item);

            Debug.Assert(item.Parent == null);

            item.Parent = this;

            if (index < children.Count)
                children.Insert(index, item);
            else
                children.Add(item);

            OnChildAdded(item);
        }

        protected bool Remove(UIVisual item)
        {
            return RemoveAt(children.IndexOf(item));
        }

        protected bool RemoveAt(int index)
        {
            if (0 <= index && index < children.Count)
            {
                UIVisual child = children[index];
                children.RemoveAt(index);
                child.Parent = null;
                OnChildRemoved(child);
                return true;
            }
            else
                return false;
        }

        protected void RemoveAll()
        {
            foreach (UIVisual item in children)
                item.Parent = null;

            children.Clear();
        }

        protected virtual void OnChildAdded(UIVisual item)
        {
        }

        protected virtual void OnChildRemoved(UIVisual item)
        {
        }

        protected virtual void OnChildrenRemoved(UIVisual item)
        {
        }

        internal void OnChildZOrderChanged(UIVisual child, int old)
        {
        }

        internal void BringChildToFront(UIVisual child)
        {
        }

        internal void SendChildToBack(UIVisual child)
        {
        }
        #endregion
    }
}
