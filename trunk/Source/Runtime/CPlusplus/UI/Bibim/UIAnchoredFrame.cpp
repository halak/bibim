#include <Bibim/PCH.h>
#include <Bibim/UIAnchoredFrame.h>

namespace Bibim
{
    UIAnchoredFrame::UIAnchoredFrame()
    {
    }

    UIAnchoredFrame::~UIAnchoredFrame()
    {
    }

    bool UIAnchoredFrame::Setup(const RectF& bounds, const RectF& referenceBounds)
    {
        return true;
    }

    RectF UIAnchoredFrame::ComputeBounds(UIVisualVisitor& /*visitor*/, Vector2 /*desiredSize*/)
    {
        return RectF::Empty;
    }
}