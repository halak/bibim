using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim
{
    public sealed class GameStructure
    {
        #region Fields
        private Dictionary<uint, GameNode> idNodes;
        #endregion

        #region Properties
        public GameNode Root
        {
            get;
            private set;
        }
        #endregion

        #region Constructors
        public GameStructure()
            : this(0)
        {
        }

        public GameStructure(int capacity)
        {
            Root = new GameNode();
            idNodes = new Dictionary<uint, GameNode>(capacity);
        }
        #endregion

        #region Methods
        public GameModule Find(uint id)
        {
            return null;
        }

        public GameNode FindNode(uint id)
        {
            return null;
        }

        #region Internal
        internal void OnModuleIDChanged(GameModule module, uint oldID)
        {
        }

        internal void OnNodeAttached(GameNode parent, GameNode child)
        {
        }

        internal void OnNodeDetached(GameNode parent, GameNode child)
        {
        }
        #endregion
        #endregion
    }
}
