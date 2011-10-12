#include <Bibim/PCH.h>
#include <Bibim/UIFixedFrame.h>
#include <Bibim/UIStreamReader.h>

namespace Bibim
{
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

    bool UIFixedFrame::Setup(const RectF& bounds, const RectF& referenceBounds)
    {
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

    UIElement* UIFixedFrame::Create(StreamReader& reader, UIElement* /*existingInstance*/)
    {
        UIFixedFrame* o = new UIFixedFrame();
        UIFrame::Read(reader, o);

        o->rect = reader.ReadRectF();

        return o;
    }

}