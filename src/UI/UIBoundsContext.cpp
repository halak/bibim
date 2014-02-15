#include <Bibim/Config.h>
#include <Bibim/UIBoundsContext.h>
#include <Bibim/UIVisual.h>
#include <Bibim/UIPanel.h>

namespace Bibim
{
    UIBoundsContext::UIBoundsContext(Point2 screenSize)
        : UIVisualVisitor(screenSize, false),
          index(-1)
    {
    }

    UIBoundsContext::~UIBoundsContext()
    {
    }

    RectF UIBoundsContext::Compute(UIVisual* target)
    {
        if (target == nullptr)
            return RectF::Empty;

        UIVisual* current = target;
        targets.push_back(current);
        while (current->GetParent())
        {
            current = current->GetParent();
            targets.push_back(current);
        }
        index = static_cast<int>(targets.size() - 1);

        Ready(targets[index]);
        Visit(targets[index--]);
        return bounds;
    }

    void UIBoundsContext::OnVisit()
    {
        if (index >= 0)
            Visit(targets[index--]);
        else
        {
            const RectF current = GetCurrentBounds();
            const Matrix4& transform = GetCurrentTransform();
            const Vector3 lt = transform.Transform(Vector3(current.GetLeft(), current.GetTop(), 0.0f));
            const Vector3 rb = transform.Transform(Vector3(current.GetRight(), current.GetBottom(), 0.0f));

            bounds = RectF(Vector2(lt.X, lt.Y), Vector2(rb.X, rb.Y));
        }
    }
}