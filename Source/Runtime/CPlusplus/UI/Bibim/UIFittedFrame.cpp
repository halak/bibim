#include <Bibim/PCH.h>
#include <Bibim/UIFittedFrame.h>
#include <Bibim/UIVisualVisitor.h>

namespace Bibim
{
    BBImplementsComponent(UIFittedFrame);

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

    void UIFittedFrame::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void UIFittedFrame::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
    }
}