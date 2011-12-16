#include <Bibim/PCH.h>
#include <Bibim/UIWindow3D.h>
#include <Bibim/UIVisualVisitor.h>

#if (defined(BIBIM_PLATFORM_WINDOWS))

#   include <d3dx9math.h>

    namespace Bibim
    {
        void UIWindow3D::UpdateMatrix(RectF bounds)
        {
            if (matrixChanged || lastBounds != bounds)
            {
                D3DXQUATERNION d3dRotation;
                D3DXQuaternionRotationYawPitchRoll(&d3dRotation, rotation.Y, rotation.X, rotation.Z);
                
                const D3DXVECTOR3 d3dScaleCenter = D3DXVECTOR3(localOffset.X + bounds.X + (bounds.Width * scaleCenter.X),
                                                               localOffset.Y + bounds.Y + (bounds.Height * scaleCenter.Y),
                                                               localOffset.Z);
                const D3DXVECTOR3 d3dScale = D3DXVECTOR3(scale.X, scale.Y, 1.0f);
                const D3DXVECTOR3 d3dRotationCenter = D3DXVECTOR3(localOffset.X + bounds.X + (bounds.Width * rotationCenter.X),
                                                                  localOffset.Y + bounds.Y + (bounds.Height * rotationCenter.Y),
                                                                  localOffset.Z);
                const D3DXVECTOR3 d3dTranslation = D3DXVECTOR3(globalOffset.X, globalOffset.Y, globalOffset.Z);

                D3DXMATRIX d3dResultTransform;
                D3DXMatrixTransformation(&d3dResultTransform, &d3dScaleCenter, nullptr, &d3dScale, &d3dRotationCenter, &d3dRotation, &d3dTranslation);

                matrix = Matrix4(d3dResultTransform);
                matrixChanged = false;
                lastBounds = bounds;
            }
        }
    }

#endif