using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace Halak.Bibim.Asset.Pipeline
{
    public abstract class GameAssetServer : GameModule
    {
        #region Properties
        public GameAssetKitchen Kitchen
        {
            get;
            set;
        }
        #endregion

        #region Constructor
        protected GameAssetServer()
            : this(null)
        {
        }

        protected GameAssetServer(GameAssetKitchen kitchen)
        {
            Kitchen = kitchen;
        }
        #endregion
    }
}
