#include <Bibim/PCH.h>
#include <Bibim/UIVisualVisitor.h>
#include <Bibim/Assert.h>
#include <Bibim/Math.h>
#include <Bibim/UIEffectMap.h>
#include <Bibim/UIGeometryEffect.h>
#include <Bibim/UITransform.h>
#include <Bibim/UIVisual.h>

namespace Bibim
{
    static const float BigFloat = 10000.0f;
    static const RectF BigRect = RectF(0.0f, 0.0f, 480.0f, 800.0f);

    UIVisualVisitor::UIVisualVisitor(bool visibleOnly)
        : visibleOnly(visibleOnly),
          currentOpacity(1.0f),
          currentBounds(BigRect),
          currentClippedBounds(BigRect),
          currentTransform(Matrix4::Identity),
          currentTransformInv(Matrix4::Identity),
          parentTransform(Matrix4::Identity),
          parentTransformInv(Matrix4::Identity),
          viewTransform(Matrix4::Identity),
          viewTransformInv(Matrix4::Identity),
          projectionTransform(Matrix4::Identity)
    {
    }

    UIVisualVisitor::UIVisualVisitor(const Matrix4& viewTransform, const Matrix4& projectionTransform, bool visibleOnly)
        : visibleOnly(visibleOnly),
          currentOpacity(1.0f),
          currentBounds(BigRect),
          currentClippedBounds(BigRect),
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
          currentBounds(BigRect),
          currentClippedBounds(BigRect),
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
        /* UNUSED
        D3DXVECTOR3 d3dPoint = D3DXVECTOR3(point.X, point.Y, 0.0f);

        D3DXVec3Project(d3dPoint, sizeof(D3DXVECTOR3), nullptr, (D3DXMATRIX*)&projectionTransform, (D3DXMATRIX*)&viewTransform, (D3DXMATRIX*)&currentTransform, 4);

        inOutPoint0 = Vector2(d3dPoints[0].x, d3dPoints[0].y);
        */
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

    void UIVisualVisitor::Project(Vector2& /*inOutPoint0*/, Vector2& /*inOutPoint1*/, Vector2& /*inOutPoint2*/, Vector2& /*inOutPoint3*/) const
    {
        /* UNUSED
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
        */
    }

    void UIVisualVisitor::Project(Vector2* /*inOutPoints*/, int /*count*/) const
    {
        /* UNUSED
        if (inOutPoints == nullptr || count == 0)
            return;

        D3DXVECTOR3* d3dPoints = BBStackAlloc(D3DXVECTOR3, count);
        for(int i = 0; i < count; ++i)
            d3dPoints[i] = D3DXVECTOR3(inOutPoints[i].X, inOutPoints[i].Y, 0.0f);

        D3DXVec3ProjectArray(d3dPoints, sizeof(D3DXVECTOR3), d3dPoints, sizeof(D3DXVECTOR3), nullptr, (D3DXMATRIX*)&projectionTransform, (D3DXMATRIX*)&viewTransform, (D3DXMATRIX*)&currentTransform, count);

        for(int i = 0; i < count; ++i)
            inOutPoints[i] = Vector2(d3dPoints[i].x, d3dPoints[i].y);

        BBStackFree(d3dPoints);
        */
    }

    void UIVisualVisitor::Visit(UIVisual* target)
    {
        BBAssert(target != nullptr);

        if (visibleOnly && target->IsVisible() == false)
            return;
        if (target->GetXMode() == UIVisual::UndefinedPosition ||
            target->GetYMode() == UIVisual::UndefinedPosition) // visible only가 아니더라도 위치가 정해지지 않으면 수행하지 않습니다.
            return;

        UIVisual*const oldVisual = currentVisual;
        const float oldOpacity = currentOpacity;
        const RectF oldBounds = currentBounds;
        const RectF oldClippedBounds = currentClippedBounds;
        UIGeometryEffect*const oldGeometryEffect = currentGeometryEffect;
        const Matrix4 oldTransform = currentTransform;
        const Matrix4 oldTransformInv = currentTransformInv;
        const Matrix4 oldParentTransform = parentTransform;
        const Matrix4 oldParentTransformInv = parentTransformInv;

        const RectF bounds = target->ComputeBounds(*this);

        currentVisual = target;
        currentOpacity *= target->GetOpacity();
        currentBounds = bounds;
        if (currentVisual->GetEffectMap() && currentVisual->GetEffectMap()->GetGeometryEffect())
            currentGeometryEffect = currentVisual->GetEffectMap()->GetGeometryEffect();
        if (target->GetPickable())
            currentClippedBounds = RectF::Intersect(currentClippedBounds, currentBounds);
        else
            currentClippedBounds = currentBounds;
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
        currentGeometryEffect = oldGeometryEffect;
        currentClippedBounds = oldClippedBounds;
        currentTransform = oldTransform;
        currentTransformInv = oldTransformInv;
        parentTransform = oldParentTransform;
        parentTransformInv = oldParentTransformInv;
    }

    static Vector3 PlaneIntersectLine(Vector4 plane, Vector3 rayStart, Vector3 rayEnd)
    {
        const Vector3 direction = rayEnd - rayStart;
        const Vector3 normal = Vector3(plane.X, plane.Y, plane.Z);
        const float dot = direction.Dot(normal);
        if (dot == 0.0f)
            return Vector3(BigFloat, BigFloat, BigFloat);

        const float t = (plane.W + normal.Dot(rayStart)) / dot;
        return rayStart - (direction * t);
    }

    Vector2 UIVisualVisitor::UnprojectPoint(Vector2 point, const Matrix4& inversedTransform) const
    {
        const RectF viewport = RectF(0, 0, 800, 600);
        const float width  = viewport.Width;
        const float height = viewport.Height;
        const Vector3 direction = Vector3(+(((2.0f * point.X) / width ) - 1.0f) / projectionTransform.M00,
                                          -(((2.0f * point.Y) / height) - 1.0f) / projectionTransform.M11,
                                          1.0f);

        const Vector3 rayOrigin = viewTransformInv.GetTranslation();
        const Vector3 rayDirection = viewTransformInv.TransformNormal(direction);

        const Vector3 transformedRayOrigin = inversedTransform.Transform(rayOrigin);
        const Vector3 transformedRayDirection = inversedTransform.TransformNormal(rayDirection);

        const Vector4 plane = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
        const Vector3 transformedRayEnd = transformedRayOrigin + (transformedRayDirection * BigFloat);
        const Vector3 pointOnPlane = PlaneIntersectLine(plane, transformedRayOrigin, transformedRayEnd);

        return Vector2(pointOnPlane.X, pointOnPlane.Y);
    }
}