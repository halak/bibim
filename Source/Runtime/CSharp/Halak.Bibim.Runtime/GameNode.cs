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

        public bool IsRoot
        {
            get { return parent != null && structure != null; }
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
        #region Children Manipulation
        public GameNode AttachChild(GameModule item)
        {
            if (item.Node == null)
                item.Node = new GameNode(item);

            AttachChild(item.Node);

            return item.Node;
        }

        public void AttachChild(GameNode item)
        {
            if (item.parent == this)
            {
                Debug.Assert(children != null && children.Contains(item));
                return;
            }

            bool structureChanged = (item.parent == null || item.parent.structure != structure);

            GameNode oldParent = item.parent;
            if (oldParent != null)
            {
                item.parent.children.Remove(item);
                item.parent = null;

                // GameStructure.OnNodeDetached의 명세대로 GameStructure가 바뀌었을 때만 호출합니다.
                if (oldParent.structure != null && structureChanged)
                    oldParent.structure.OnNodeDetached(oldParent, item);
            }

            Debug.Assert(item.parent == null);

            item.parent = this;
            item.structure = structure;

            if (children == null)
                children = new List<GameNode>();

            children.Add(item);

            // GameStructure.OnNodeAttached의 명세대로 GameStructure가 바뀌었을 때만 호출합니다.
            if (structure != null && structureChanged)
                structure.OnNodeAttached(this, item);
        }

        public bool DetachChild(GameModule item)
        {
            if (item.Node != null)
                return DetachChild(item.Node);
            else
                return false;
        }

        public bool DetachChild(GameNode item)
        {
            if (children == null || item.parent != this || item.structure != structure)
                return false;

            if (children.Remove(item))
            {
                item.parent = null;

                if (structure != null)
                    structure.OnNodeDetached(this, item);

                return true;
            }
            else
                return false;
        }

        public void DetachAllChildren()
        {
            if (children == null)
                return;

            List<GameNode> temporaryChildren = children;

            if (structure != null)
            {
                foreach (GameNode item in temporaryChildren)
                {
                    Debug.Assert(item.parent != null);

                    structure.OnNodeDetached(this, item);

                    item.parent = null;
                }
            }
            else
            {
                foreach (GameNode item in temporaryChildren)
                {
                    Debug.Assert(item.parent != null);

                    item.parent = null;
                }
            }
        }
        #endregion

        #region Find
        public GameModule FindChild(uint id, bool searchAllChildren)
        {
            GameNode node = FindChildNode(id, searchAllChildren);
            if (node != null)
                return node.Module;
            else
                return null;
        }

        public GameModule FindChildByClassID(uint classID, bool searchAllChildren)
        {
            GameNode node = FindChildNodeByClassID(classID, searchAllChildren);
            if (node != null)
                return node.Module;
            else
                return null;
        }

        public GameNode FindChildNode(uint id, bool searchAllChildren)
        {
            if (id == GameModule.UnspecifiedID)
                return null;

            if (searchAllChildren)
            {
                foreach (GameNode item in children)
                {
                    if (item.Module != null && item.Module.ID == id)
                        return item;

                    GameNode foundNode = FindChildNode(id, searchAllChildren);
                    if (foundNode != null)
                        return foundNode;
                }
            }
            else
            {
                foreach (GameNode item in children)
                {
                    if (item.Module != null && item.Module.ID == id)
                        return item;
                }
            }

            return null;
        }

        public GameNode FindChildNodeByClassID(uint classID, bool searchAllChildren)
        {
            if (searchAllChildren)
            {
                foreach (GameNode item in children)
                {
                    if (item.Module != null && item.Module.ClassID == classID)
                        return item;

                    GameNode foundNode = FindChildNodeByClassID(classID, searchAllChildren);
                    if (foundNode != null)
                        return foundNode;
                }
            }
            else
            {
                foreach (GameNode item in children)
                {
                    if (item.Module != null && item.Module.ClassID == classID)
                        return item;
                }
            }

            return null;
        }
        #endregion
        #endregion
    }
}
