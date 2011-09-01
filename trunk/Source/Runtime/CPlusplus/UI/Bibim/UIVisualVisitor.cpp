#include <Bibim/PCH.h>
#include <Bibim/UIVisualVisitor.h>
#include <Bibim/Assert.h>
#include <Bibim/Math.h>
#include <Bibim/UIFrame.h>
#include <Bibim/UITransform.h>
#include <Bibim/UIVisual.h>
#include <d3dx9.h>

namespace Bibim
{
    static const float BigFloat = 10000.0f;
    static const RectangleF BigRectangle = RectangleF(-BigFloat, -BigFloat, BigFloat + BigFloat, BigFloat + BigFloat);

    UIVisualVisitor::UIVisualVisitor(const Matrix4& viewTransform, const Matrix4& projectionTransform, bool visibleOnly)
        : visibleOnly(visibleOnly),
          currentOpacity(1.0f),
          currentBounds(BigRectangle),
          currentClippedBounds(BigRectangle),
          currentTransform(Matrix4::Identity),
          currentTransformInv(Matrix4::Identity),
          parentTransform(Matrix4::Identity),
          parentTransformInv(Matrix4::Identity),
          viewTransform(viewTransform),
          viewTransformInv(Matrix4::Inversion(viewTransform)),
          projectionTransform(projectionTransform)
    {
    }

    UIVisualVisitor::UIVisualVisitor(const Matrix4& viewTransform, const Matrix4& viewTransformInv, const Matrix4& projectionTransform, bool visibleOnly)
        : visibleOnly(visibleOnly),
          currentOpacity(1.0f),
          currentBounds(BigRectangle),
          currentClippedBounds(BigRectangle),
          currentTransform(Matrix4::Identity),
          currentTransformInv(Matrix4::Identity),
          parentTransform(Matrix4::Identity),
          parentTransformInv(Matrix4::Identity),
          viewTransform(viewTransform),
          viewTransformInv(viewTransformInv),
          projectionTransform(projectionTransform)
    {
        BBAssertDebug(Matrix4::Inversion(viewTransform) == viewTransformInv);
    }

    UIVisualVisitor::~UIVisualVisitor()
    {
    }

    Vector2 UIVisualVisitor::Project(Vector2 point) const
    {
        //D3DXVECTOR3 d3dPoint = D3DXVECTOR3(point.X, point.Y, 0.0f);

        //D3DXVec3Project(d3dPoints, sizeof(D3DXVECTOR3), nullptr, (D3DXMATRIX*)&projectionTransform, (D3DXMATRIX*)&viewTransform, (D3DXMATRIX*)&currentTransform, 4);

        //inOutPoint0 = Vector2(d3dPoints[0].x, d3dPoints[0].y);

        return point;
    }

    Vector2 UIVisualVisitor::Unproject(Vector2 point) const
    {
        return UnprojectPoint(point, currentTransformInv);
    }

    Vector2 UIVisualVisitor::UnprojectByParent(Vector2 point) const
    {
        return UnprojectPoint(point, parentTransformInv);
    }

    void UIVisualVisitor::Project(Vector2& inOutPoint0, Vector2& inOutPoint1, Vector2& inOutPoint2, Vector2& inOutPoint3) const
    {
        D3DXVECTOR3 d3dPoints[4] =
        {
            D3DXVECTOR3(inOutPoint0.X, inOutPoint0.Y, 0.0f),
            D3DXVECTOR3(inOutPoint1.X, inOutPoint1.Y, 0.0f),
            D3DXVECTOR3(inOutPoint2.X, inOutPoint2.Y, 0.0f),
            D3DXVECTOR3(inOutPoint3.X, inOutPoint3.Y, 0.0f),
        };

        D3DXVec3ProjectArray(d3dPoints, sizeof(D3DXVECTOR3), d3dPoints, sizeof(D3DXVECTOR3), nullptr, (D3DXMATRIX*)&projectionTransform, (D3DXMATRIX*)&viewTransform, (D3DXMATRIX*)&currentTransform, 4);

        inOutPoint0 = Vector2(d3dPoints[0].x, d3dPoints[0].y);
        inOutPoint1 = Vector2(d3dPoints[1].x, d3dPoints[1].y);
        inOutPoint2 = Vector2(d3dPoints[2].x, d3dPoints[2].y);
        inOutPoint3 = Vector2(d3dPoints[3].x, d3dPoints[3].y);
    }

    void UIVisualVisitor::Project(Vector2* inOutPoints, int count) const
    {
        if (inOutPoints == nullptr || count == 0)
            return;

        D3DXVECTOR3* d3dPoints = BBStackAlloc(D3DXVECTOR3, count);
        for(int i = 0; i < count; ++i)
            d3dPoints[i] = D3DXVECTOR3(inOutPoints[i].X, inOutPoints[i].Y, 0.0f);

        D3DXVec3ProjectArray(d3dPoints, sizeof(D3DXVECTOR3), d3dPoints, sizeof(D3DXVECTOR3), nullptr, (D3DXMATRIX*)&projectionTransform, (D3DXMATRIX*)&viewTransform, (D3DXMATRIX*)&currentTransform, count);

        for(int i = 0; i < count; ++i)
            inOutPoints[i] = Vector2(d3dPoints[i].x, d3dPoints[i].y);

        BBStackFree(d3dPoints);
    }

    void UIVisualVisitor::Visit(UIVisual* target)
    {
        BBAssert(target != nullptr);

        if (visibleOnly && target->IsVisible() == false)
            return;
        if (target->GetFrame() == nullptr) // visible only가 아니더라도 Frame이 없으면 작업을 수행하지 않는다.
            return;

        UIVisual*const oldVisual = currentVisual;
        const float oldOpacity = currentOpacity;
        const RectangleF oldBounds = currentBounds;
        const RectangleF oldClippedBounds = currentClippedBounds;
        const Matrix4 oldTransform = currentTransform;
        const Matrix4 oldTransformInv = currentTransformInv;
        const Matrix4 oldParentTransform = parentTransform;
        const Matrix4 oldParentTransformInv = parentTransformInv;

        const RectangleF bounds = target->ComputeBounds(*this);

        currentVisual = target;
        currentOpacity *= target->GetOpacity();
        currentBounds = bounds;
        currentClippedBounds = RectangleF::Intersect(currentClippedBounds, currentBounds);
        parentTransform = currentTransform;
        parentTransformInv = currentTransformInv;
        if (target->GetTransform())
        {
            currentTransform *= target->GetTransform()->ComputeMatrix(*this);
            currentTransformInv = Matrix4::Inversion(currentTransform);
        }

        OnVisit();

        currentVisual = oldVisual;
        currentOpacity = oldOpacity;
        currentBounds = oldBounds;
        currentClippedBounds = oldClippedBounds;
        currentTransform = oldTransform;
        currentTransformInv = oldTransformInv;
        parentTransform = oldParentTransform;
        parentTransformInv = oldParentTransformInv;
    }

    Vector2 UIVisualVisitor::UnprojectPoint(Vector2 point, const Matrix4& inversedTransform) const
    {
        const float width  = 800.0f;
        const float height = 600.0f;
        const D3DXVECTOR3 direction = D3DXVECTOR3(+(((2.0f * point.X) / width ) - 1.0f) / projectionTransform.M00,
                                                  -(((2.0f * point.Y) / height) - 1.0f) / projectionTransform.M11,
                                                  1.0f);

        const D3DXVECTOR3 rayDirection = D3DXVECTOR3((direction.x * viewTransformInv.M00 + direction.y * viewTransformInv.M10 + direction.z * viewTransformInv.M20),
                                                     (direction.x * viewTransformInv.M01 + direction.y * viewTransformInv.M11 + direction.z * viewTransformInv.M21),
                                                     (direction.x * viewTransformInv.M02 + direction.y * viewTransformInv.M12 + direction.z * viewTransformInv.M22));
        const D3DXVECTOR3 rayOrigin = D3DXVECTOR3(viewTransformInv.M30, viewTransformInv.M31, viewTransformInv.M32);

        D3DXVECTOR3 transformedRayOrigin;
        D3DXVECTOR3 transformedRayDirection;
        D3DXVec3TransformCoord(&transformedRayOrigin, &rayOrigin, (const D3DXMATRIX*)&inversedTransform);
        D3DXVec3TransformNormal(&transformedRayDirection, &rayDirection, (const D3DXMATRIX*)&inversedTransform);

        D3DXVECTOR3 pointOnPlane;
        const D3DXPLANE plane = D3DXPLANE(0.0f, 0.0f, 1.0f, 0.0f);
        const D3DXVECTOR3 transformedRayEnd = transformedRayOrigin + (transformedRayDirection * BigFloat);
        D3DXPlaneIntersectLine(&pointOnPlane, &plane, &transformedRayOrigin, &transformedRayEnd);

        return Vector2(pointOnPlane.x, pointOnPlane.y);
    }
}