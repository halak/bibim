#include <Bibim/PCH.h>
#include <Bibim/UIFixedFrame.h>

namespace Bibim
{
    UIFixedFrame::UIFixedFrame()
        : UIFrame(),
          Rect(RectF::Empty)
    {
    }

    UIFixedFrame::UIFixedFrame(const RectF& Rect)
        : UIFrame(),
          Rect(Rect)
    {
    }

    UIFixedFrame::~UIFixedFrame()
    {
    }

    bool UIFixedFrame::Setup(const RectF& bounds, const RectF& referenceBounds)
    {
        return true;
    }

    RectF UIFixedFrame::ComputeBounds(UIVisualVisitor& /*visitor*/, Vector2 desiredSize)
    {
        RectF result = Rect;
        if (desiredSize.X >= 0.0f)
            result.Width = desiredSize.X;
        if (desiredSize.Y >= 0.0f)
            result.Height = desiredSize.Y;

        return result;
    }

    void UIFixedFrame::Move(Vector2 displacement)
    {
        Rect.X += displacement.X;
        Rect.Y += displacement.Y;
    }

    bool UIFixedFrame::IsMovable() const
    {
        return true;
    }

    void UIFixedFrame::Resize(float left, float top, float right, float bottom)
    {
        const float boundsLeft   = Rect.GetLeft() - left;
        const float boundsTop    = Rect.GetTop() - top;
        const float boundsRight  = Rect.GetRight() + right;
        const float boundsBottom = Rect.GetBottom() + bottom;
        Rect = RectF(boundsLeft, boundsTop, boundsRight - boundsLeft, boundsBottom - boundsTop);
    }

    void UIFixedFrame::ResizeTo(Vector2 size)
    {
        Rect.Width  = size.X;
        Rect.Height = size.Y;
    }

    bool UIFixedFrame::IsResizable() const
    {
        return true;
    }
}