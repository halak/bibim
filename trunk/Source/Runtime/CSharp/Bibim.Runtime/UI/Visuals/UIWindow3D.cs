using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;

namespace Bibim.UI.Visuals
{
    [ClassID('U', 'W', 'N', '3')]
    public class UIWindow3D : UIWindow
    {
        #region Fields
        Vector3 localOffset;
        Vector3 globalOffset;
        Vector2 rotationCenter;
        Vector3 rotation;
        Vector2 scaleCenter;
        Vector2 scale;
        Matrix matrix;
        RectangleF lastBounds;
        bool matrixChanged;
        #endregion

        #region Properties
        public Vector3 LocalOffset
        {
            get { return localOffset; }
            set
            {
                if (localOffset != value)
                {
                    localOffset = value;
                    matrixChanged = true;
                }
            }
        }

        public Vector3 GlobalOffset
        {
            get { return globalOffset; }
            set
            {
                if (globalOffset != value)
                {
                    globalOffset = value;
                    matrixChanged = true;
                }
            }
        }

        public Vector2 RotationCenter
        {
            get { return rotationCenter; }
            set
            {
                if (rotationCenter != value)
                {
                    rotationCenter = value;
                    matrixChanged = true;
                }
            }
        }

        public Vector3 Rotation
        {
            get { return rotation; }
            set
            {
                if (rotation != value)
                {
                    rotation = value;
                    matrixChanged = true;
                }
            }
        }

        public Vector2 ScaleCenter
        {
            get { return scaleCenter; }
            set
            {
                if (scaleCenter != value)
                {
                    scaleCenter = value;
                    matrixChanged = true;
                }
            }
        }

        public Vector2 Scale
        {
            get { return scale; }
            set
            {
                if (scale != value)
                {
                    scale = value;
                    matrixChanged = true;
                }
            }
        }
        #endregion

        #region Constructors
        public UIWindow3D()
        {
        }
        #endregion

        #region Methods
        #endregion
    }
}
