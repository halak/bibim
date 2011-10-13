#include <Bibim/PCH.h>
#include <Bibim/UIFixedFrame.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    BBImplementsComponent(UIFixedFrame);

    UIFixedFrame::UIFixedFrame()
        : UIFrame(),
          rect(RectF::Empty)
    {
    }

    UIFixedFrame::UIFixedFrame(const RectF& rect)
        : UIFrame(),
          rect(rect)
    {
    }

    UIFixedFrame::~UIFixedFrame()
    {
    }

    bool UIFixedFrame::Setup(const RectF& bounds, const RectF& /*referenceBounds*/)
    {
        rect = bounds;
        return true;
    }

    RectF UIFixedFrame::ComputeBounds(UIVisualVisitor& /*visitor*/, Vector2 desiredSize)
    {
        RectF result = rect;
        if (desiredSize.X >= 0.0f)
            result.Width = desiredSize.X;
        if (desiredSize.Y >= 0.0f)
            result.Height = desiredSize.Y;

        return result;
    }

    void UIFixedFrame::Move(Vector2 displacement)
    {
        rect.X += displacement.X;
        rect.Y += displacement.Y;
    }

    bool UIFixedFrame::IsMovable() const
    {
        return true;
    }

    void UIFixedFrame::Resize(float left, float top, float right, float bottom)
    {
        const float boundsLeft   = rect.GetLeft() - left;
        const float boundsTop    = rect.GetTop() - top;
        const float boundsRight  = rect.GetRight() + right;
        const float boundsBottom = rect.GetBottom() + bottom;
        rect = RectF(boundsLeft, boundsTop, boundsRight - boundsLeft, boundsBottom - boundsTop);
    }

    void UIFixedFrame::ResizeTo(Vector2 size)
    {
        rect.Width  = size.X;
        rect.Height = size.Y;
    }

    bool UIFixedFrame::IsResizable() const
    {
        return true;
    }

    void UIFixedFrame::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        rect = reader.ReadRectF();
    }

    void UIFixedFrame::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const UIFixedFrame* o = static_cast<const UIFixedFrame*>(original);
        rect = o->rect;
    }
}