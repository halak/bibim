using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using Bibim.Graphics;
using Microsoft.Xna.Framework;
using XnaWindow = Microsoft.Xna.Framework.GameWindow;

namespace Bibim.Framework
{
    public abstract class GameWindow : Window
    {
        #region Fields
        private XnaWindow o;
        #endregion

        #region Properties
        public override Point2 Position
        {
            get
            {
                throw new NotImplementedException();
            }

            set
            {
                throw new NotImplementedException();
            }
        }

        public override Point2 Size
        {
            get
            {
                Rectangle bounds = o.ClientBounds;
                Point2 result = Point2.Zero;
                result.X = bounds.Width;
                result.Y = bounds.Height;
                //o.AllowUserResizing;
                return result;
            }
            set
            {
            }
        }

        public override bool Visible
        {
            get { return true; }
            set
            {
            }
        }
        #endregion

        #region Constructors
        internal GameWindow(XnaWindow o)
        {
            Trace.Assert(o != null);
            this.o = o;
        }
        #endregion

        #region Methods
        public override void Close()
        {
        }
        #endregion
    }
}
