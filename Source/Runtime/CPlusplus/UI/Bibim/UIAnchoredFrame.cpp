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

    bool UIAnchoredFrame::Setup(const RectangleF& bounds, const RectangleF& referenceBounds)
    {
        return true;
    }

    RectangleF UIAnchoredFrame::ComputeBounds(UIVisualVisitor& /*visitor*/, Vector2 /*desiredSize*/)
    {
        return RectangleF::Empty;
    }
}