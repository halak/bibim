#include <Bibim/PCH.h>
#include <Bibim/UIFlowPanel.h>

namespace Bibim
{
    UIFlowPanel::UIFlowPanel()
        : direction(LeftToRight)
    {
    }

    UIFlowPanel::~UIFlowPanel()
    {
    }

    void UIFlowPanel::SetDirection(Direction value)
    {
        direction = value;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIFlowPanel::ArrangedFrame::ArrangedFrame()
        : Offset(Vector2::Zero),
          Size(Vector2::Zero),
          IsNewLine(false)
    {
    }

    UIFlowPanel::ArrangedFrame::ArrangedFrame(Vector2 offset, Vector2 size, bool isNewLine)
        : Offset(offset),
          Size(size),
          IsNewLine(isNewLine)
    {
    }

    UIFlowPanel::ArrangedFrame::~ArrangedFrame()
    {
    }

    bool UIFlowPanel::ArrangedFrame::Setup(const RectangleF& /*bounds*/, const RectangleF& /*referenceBounds*/)
    {
        return false;
    }

    RectangleF UIFlowPanel::ArrangedFrame::ComputeBounds(UIVisualVisitor& visitor, Vector2 /*desiredSize*/)
    {
        //const RectangleF bounds = context.GetCurrentBounds();
        //const RectangleF previousBounds = context.GetPreviousBounds();

        //RectangleF result = RectangleF::Empty;
        //if (owner->GetParent()->GetChildren()[0] != owner)
        //{
        //    result.X = previousBounds.GetRight();
        //    result.Y = previousBounds.GetTop();
        //    result.Width = Size.X;
        //    result.Height = Size.Y;
        //}
        //else
        //{
        //    result.X = bounds.GetLeft();
        //    result.Y = bounds.GetTop();
        //    result.Width = Size.X;
        //    result.Height = Size.Y;
        //}
        //return result;
        return visitor.GetCurrentBounds();
    }
}