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

    bool UIFittedFrame::Setup(const RectF& /*bounds*/, const RectF& /*referenceBounds*/)
    {
        return false;
    }

    RectF UIFittedFrame::ComputeBounds(UIVisualVisitor& visitor, Vector2 /*desiredSize*/)
    {
        return visitor.GetCurrentBounds();
    }
}