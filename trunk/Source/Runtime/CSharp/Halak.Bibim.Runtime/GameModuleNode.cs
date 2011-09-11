using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;

namespace Halak.Bibim
{
    public sealed class GameModuleNode
    {
        #region Fields
        private GameModule module;
        private GameModuleNode parent;
        private List<GameModuleNode> children;
        private GameModuleTree tree;
        #endregion

        #region Properties
        public GameModule Module
        {
            get { return module; }
        }

        public GameModuleNode Parent
        {
            get { return parent; }
        }

        public IEnumerable<GameModuleNode> Children
        {
            get { return children; }
        }

        public GameModuleTree Tree
        {
            get { return tree; }
            internal set
            {
                tree = value;
            }
        }

        public bool IsRoot
        {
            get { return parent != null && tree != null; }
        }
        #endregion

        #region Constructors
        public GameModuleNode()
        {
        }

        public GameModuleNode(GameModule module)
        {
            this.module = module;
        }

        public GameModuleNode(GameModule module, int childrenCapacity)
            : this(module)
        {
            children = new List<GameModuleNode>(childrenCapacity);
        }
        #endregion

        #region Methods
        #region Children Manipulation
        public GameModuleNode AttachChild(GameModule item)
        {
            if (item.Node == null)
                item.Node = new GameModuleNode(item);

            AttachChild(item.Node);

            return item.Node;
        }

        public void AttachChild(GameModuleNode item)
        {
            if (item.parent == this)
            {
                Debug.Assert(children != null && children.Contains(item));
                return;
            }

            bool treeChanged = (item.parent == null || item.parent.tree != tree);

            GameModuleNode oldParent = item.parent;
            if (oldParent != null)
            {
                // Detach를 거치지 않고 직접 제거합니다.
                item.parent.children.Remove(item);
                item.parent = null;

                // GameStructure.OnNodeDetached의 명세대로 GameStructure가 바뀌었을 때만 호출합니다.
                if (oldParent.tree != null && treeChanged)
                    oldParent.tree.OnNodeDetached(oldParent, item);
            }

            Debug.Assert(item.parent == null);

            item.parent = this;
            item.tree = tree;
            if (children == null)
                children = new List<GameModuleNode>();
            children.Add(item);

            // GameStructure.OnNodeAttached의 명세대로 GameStructure가 바뀌었을 때만 호출합니다.
            if (tree != null && treeChanged)
                tree.OnNodeAttached(this, item);
        }

        public bool DetachChild(GameModuleNode item)
        {
            if (children == null || item.parent != this || item.tree != tree)
                return false;

            bool removed = children.Remove(item);
            Debug.Assert(removed); // 이미 item의 부모가 this인지 확인했기 때문에 반드시 있어야합니다.

            item.parent = null;

            if (tree != null)
                tree.OnNodeDetached(this, item);

            return true;
        }

        public void DetachAllChildren()
        {
            if (children == null)
                return;

            List<GameModuleNode> temporaryChildren = children;

            if (tree != null)
            {
                for (int i = temporaryChildren.Count - 1; i >= 0; i--)
                {
                    GameModuleNode item = temporaryChildren[i];
                    tree.OnNodeDetached(this, item);
                    item.parent = null;
                }
            }
            else
            {
                for (int i = temporaryChildren.Count - 1; i >= 0; i--)
                    temporaryChildren[i].parent = null;
            }
        }
        #endregion

        #region Find
        public GameModule FindChild(uint id)
        {
            GameModuleNode node = FindChildNode(id);
            if (node != null)
                return node.Module;
            else
                return null;
        }

        public GameModule FindChildByClassID(uint classID)
        {
            GameModuleNode node = FindChildNodeByClassID(classID);
            if (node != null)
                return node.Module;
            else
                return null;
        }

        public GameModuleNode FindChildNode(uint id)
        {
            if (id == GameModule.UnspecifiedID)
                return null;

            foreach (GameModuleNode item in children)
            {
                if (item.Module != null && item.Module.ID == id)
                    return item;

            }

            foreach (GameModuleNode item in children)
            {
                GameModuleNode foundNode = FindChildNode(id);
                if (foundNode != null)
                    return foundNode;
            }

            return null;
        }

        public GameModuleNode FindChildNodeByClassID(uint classID)
        {
            foreach (GameModuleNode item in children)
            {
                if (item.Module != null && item.Module.ClassID == classID)
                    return item;
            }

            foreach (GameModuleNode item in children)
            {
                GameModuleNode foundNode = FindChildNodeByClassID(classID);
                if (foundNode != null)
                    return foundNode;
            }

            return null;
        }

        public GameModuleNode FindChildNode(GameModule item)
        {
            // 원래는 모든 자식 Node들을 순회하며 검사해야하지만,
            // GameModule에서 자신을 가진 Node를 아는 관계로 최적화할 수 있었습니다.
            // GameModule의 조상Node중 this가 있는지 확인합니다.

            if (item.Node == null || item.Node.tree != tree)
                return null;

            if (IsAncestor(item.Node, this))
                return item.Node;
            else
                return null;
        }

        private static bool IsAncestor(GameModuleNode descendant, GameModuleNode ancestor)
        {
            if (descendant.parent == null)
                return false;
            if (descendant.parent == ancestor)
                return true;
            else
                return IsAncestor(descendant.parent, ancestor);
        }
        #endregion

        #region Internal
        internal void OnModuleAliveChanged()
        {
            // Alive => 상위 GameModule와 하위 GameModule들을 모두 Alive로 만듭니다.
            // Dead  => 하위 GameModule들을 모두 Dead상태로 만듭니다.

            bool alive = module.Alive;

            if (alive && parent != null)
                parent.module.Alive = true;
            foreach (GameModuleNode item in children)
                item.module.Alive = alive;
        }
        #endregion
        #endregion
    }
}
