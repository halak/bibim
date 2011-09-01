#include <Bibim/PCH.h>
#include <Bibim/UIFittedFrame.h>
#include <Bibim/UIVisualVisitor.h>

namespace Bibim
{
    UIFittedFramePtr UIFittedFrame::Instance = new UIFittedFrame();

    UIFittedFrame::UIFittedFrame()
    {
    }

    UIFittedFrame::~UIFittedFrame()
    {
    }

    bool UIFittedFrame::Setup(const RectangleF& /*bounds*/, const RectangleF& /*referenceBounds*/)
    {
        return false;
    }

    RectangleF UIFittedFrame::ComputeBounds(UIVisualVisitor& visitor, Vector2 /*desiredSize*/)
    {
        return visitor.GetCurrentBounds();
    }
}