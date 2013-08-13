using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using Bibim.Asset;

namespace Bibim.Graphics
{
    public abstract class Texture2D : GameAsset
    {
        #region PixelFormat (Nested Enum)
        public enum PixelFormat
        {
            Unknown,
            A8R8G8B8,
            A8,
            A8A8A8A8,
        }
        #endregion

        #region Fields
        private GraphicsDevice graphicsDevice;
        #endregion

        #region Properties
        public GraphicsDevice GraphicsDevice
        {
            get { return graphicsDevice; }
            set
            {
                if (graphicsDevice != value)
                {
                    graphicsDevice = value;
                }
            }
        }

        public int Width
        {
            get;
            private set;
        }

        public int Height
        {
            get;
            private set;
        }

        public int SurfaceWidth
        {
            get;
            private set;
        }

        public int SurfaceHeight
        {
            get;
            private set;
        }

        public PixelFormat Format
        {
            get;
            private set;
        }
        #endregion

        #region Constructors
        public Texture2D()
        {
        }

        public Texture2D(GraphicsDevice graphicsDevice)
        {
            this.graphicsDevice = graphicsDevice;
        }
        #endregion

        #region Methods
        protected void Setup(int width, int height, int surfaceWidth, int surfaceHeight, PixelFormat format)
        {
            Width = width;
            Height = height;
            SurfaceWidth = surfaceWidth;
            SurfaceHeight = surfaceHeight;
            Format = format;
        }
        #endregion
    }
}
