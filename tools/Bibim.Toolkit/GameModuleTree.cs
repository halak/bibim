using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;

namespace Bibim
{
    public sealed class GameModuleTree
    {
        #region Fields
        private Dictionary<int, GameModuleNode> idNodes;
        #endregion

        #region Properties
        public GameModuleNode Root
        {
            get;
            private set;
        }
        #endregion

        #region Constructors
        public GameModuleTree()
            : this(0)
        {
        }

        public GameModuleTree(int capacity)
        {
            Root = new GameModuleNode();
            idNodes = new Dictionary<int, GameModuleNode>(capacity);
        }
        #endregion

        #region Methods
        public GameModule Find(int id)
        {
            GameModuleNode foundNode = null;
            if (idNodes.TryGetValue(id, out foundNode))
                return foundNode.Module;
            else
                return null;
        }

        public GameModuleNode FindNode(int id)
        {
            GameModuleNode foundNode = null;
            if (idNodes.TryGetValue(id, out foundNode))
                return foundNode;
            else
                return null;
        }

        #region Internal
        internal void OnModuleIDChanged(GameModule module, int oldID)
        {
            Debug.Assert(module.Node != null && module.Node.Tree == this);

            if (oldID != GameModule.UnspecifiedID)
                idNodes.Remove(oldID);

            int id = module.ID;
            if (id != GameModule.UnspecifiedID)
                idNodes.Add(id, module.Node);
        }

        internal void OnNodeAttached(GameModuleNode parent, GameModuleNode child)
        {
            Debug.Assert(parent.Tree == this);
            SetContainerAndRegisterID(child);
        }

        internal void OnNodeDetached(GameModuleNode parent, GameModuleNode child)
        {
            Debug.Assert(parent.Tree == this);
            ResetContainerAndRegisterID(child);
        }

        private void SetContainerAndRegisterID(GameModuleNode node)
        {
            // GameModuleTree에서 이 Method를 호출하기 전에 검사하여 예외를 던져야합니다.
            Debug.Assert(idNodes.ContainsKey(node.Module.ID));

            node.Tree = this;

            int id = node.Module.ID;
            if (id != GameModule.UnspecifiedID)
                idNodes.Add(id, node);

            foreach (GameModuleNode item in node.Children)
                SetContainerAndRegisterID(item);
        }

        private void ResetContainerAndRegisterID(GameModuleNode node)
        {
            node.Tree = null;

            int id = node.Module.ID;
            if (id != GameModule.UnspecifiedID)
                idNodes.Remove(id);

            foreach (GameModuleNode item in node.Children)
                ResetContainerAndRegisterID(item);
        }
        #endregion

        #region Static Methods
        public uint GenerateID()
        {
            return 0;
        }
        #endregion
        #endregion
    }
}
