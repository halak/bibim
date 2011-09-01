using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;

namespace Halak.Bibim
{
    public sealed class GameNode
    {
        #region Fields
        private GameModule module;
        private GameNode parent;
        private List<GameNode> children;
        private GameStructure structure;
        #endregion

        #region Properties
        public GameModule Module
        {
            get { return module; }
        }

        public GameNode Parent
        {
            get { return parent; }
        }

        public IEnumerable<GameNode> Children
        {
            get { return children; }
        }

        public GameStructure Structure
        {
            get { return structure; }
            internal set
            {
                structure = value;
            }
        }
        #endregion

        #region Constructors
        public GameNode()
        {
        }

        public GameNode(GameModule module)
        {
            this.module = module;
        }

        public GameNode(GameModule module, int childrenCapacity)
            : this(module)
        {
            children = new List<GameNode>(childrenCapacity);
        }
        #endregion

        #region Methods
        public void AttachChild(GameNode item)
        {
            if (item.parent != null)
                item.parent.DetachChild(item);

            Debug.Assert(item.parent == null);

            item.parent = this;
            children.Add(item);
        }

        public bool DetachChild(GameNode item)
        {
            if (children.Remove(item))
            {
                item.parent = null;
                return true;
            }
            else
                return false;
        }

        public bool DetachChild(GameModule item)
        {
            if (item.Node != null)
                return DetachChild(item.Node);
            else
                return false;
        }

        public void DetachAllChildren()
        {
            List<GameNode> temporaryChildren = children;
            children = null;

            foreach(GameNode item in temporaryChildren)
            {
                Debug.Assert(item.parent != null);

                item.parent = null;
            }
        }
        #endregion
    }
}
