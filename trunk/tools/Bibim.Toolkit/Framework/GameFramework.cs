using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using XnaGame = Microsoft.Xna.Framework.Game;

namespace Bibim.Framework
{
    public abstract class GameFramework : IDisposable
    {
        #region Fields
        private Game proxy;
        private bool alreadyDisposed;
        #endregion

        #region Properties
        #endregion

        protected GameFramework()
        {
            proxy = new Game(this);
            alreadyDisposed = false;
        }

        ~GameFramework()
        {
            Dispose(false);
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool isDisposing)
        {
            if (alreadyDisposed)
                return;

            if (isDisposing)
                proxy.Dispose();

            alreadyDisposed = true;
        }

        private sealed class Game : XnaGame
        {
            private GameFramework o;

            public Game(GameFramework o)
            {
                this.o = o;
            }
        }
    }
}
