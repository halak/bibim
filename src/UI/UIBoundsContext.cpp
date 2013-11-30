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
            bounds = GetCurrentBounds();
    }
}