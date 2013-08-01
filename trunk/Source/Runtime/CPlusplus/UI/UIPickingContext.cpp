#include <Bibim/Config.h>
#include <Bibim/UIPickingContext.h>
#include <Bibim/GraphicsDevice.h>
#include <Bibim/UIRenderer.h>
#include <Bibim/UIVisual.h>

namespace Bibim
{
    UIPickingContext::UIPickingContext(UIRenderer* renderer, Vector2 point)
        : UIVisualVisitor(renderer->GetGraphicsDevice()->GetViewportSize(),
                          renderer->GetViewTransform(),
                          renderer->GetInversedViewTransform(),
                          renderer->GetProjectionTransform(),
                          true),
          point(point),
          currentPoint(point),
          result(nullptr)
    {
    }

    UIPickingContext::UIPickingContext(UIRenderer* renderer, Vector2 point, bool visibleOnly)
        : UIVisualVisitor(renderer->GetGraphicsDevice()->GetViewportSize(),
                          renderer->GetViewTransform(),
                          renderer->GetInversedViewTransform(),
                          renderer->GetProjectionTransform(),
                          visibleOnly),
          point(point),
          currentPoint(point),
          result(nullptr)
    {
    }

    UIPickingContext::~UIPickingContext()
    {
    }

    bool UIPickingContext::Pick(UIVisual* target)
    {
        Ready(target);
        Visit(target);
        return GetResult() != nullptr;
    }

    void UIPickingContext::SetResult(UIVisual* value)
    {
        this->result = value;
    }

    void UIPickingContext::OnVisit()
    {
        const Vector2 oldPoint = currentPoint;

        currentPoint = Unproject(point);

        GetCurrentVisual()->OnPick(*this);

        currentPoint = oldPoint;
    }
}