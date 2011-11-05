#include <Bibim/PCH.h>
#include <Bibim/UIAlignedFrame.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/UIVisualVisitor.h>

namespace Bibim
{
    BBImplementsComponent(UIAlignedFrame);

    UIAlignedFrame::UIAlignedFrame()
        : UIFrame(),
          align(LeftTop),
          offset(Vector2::Zero),
          size(Vector2::Zero),
          lastBounds(RectF::Empty),
          lastReferenceBounds(RectF::Empty),
          boundsChanged(true)
    {
    }

    UIAlignedFrame::UIAlignedFrame(Vector2 offset, Vector2 size)
        : UIFrame(),
          align(LeftTop),
          offset(offset),
          size(size),
          lastBounds(RectF::Empty),
          lastReferenceBounds(RectF::Empty),
          boundsChanged(true)
    {
    }

    UIAlignedFrame::UIAlignedFrame(Alignment align, Vector2 offset, Vector2 size)
        : UIFrame(),
          align(align),
          offset(offset),
          size(size),
          lastBounds(RectF::Empty),
          lastReferenceBounds(RectF::Empty),
          lastDesiredSize(Vector2::Zero),
          boundsChanged(true)
    {
    }

    UIAlignedFrame::~UIAlignedFrame()
    {
    }

    bool UIAlignedFrame::Setup(const RectF& bounds, const RectF& referenceBounds)
    {
        Vector2 offset = Vector2::Zero;

        switch (GetAlign())
        {
            case LeftTop:
            case LeftBottom:
            case LeftMiddle:
                offset.X = bounds.GetLeft() - referenceBounds.GetLeft();
                break;
            case RightTop:
            case RightBottom:
            case RightMiddle:
                offset.X = referenceBounds.GetRight() - bounds.GetRight();
                break;
            case CenterTop:
            case CenterBottom:
            case Center:
                offset.X = bounds.GetCenter() - referenceBounds.GetCenter();
                break;
        }

        switch (GetAlign())
        {
            case LeftTop:
            case RightTop:
            case CenterTop:
                offset.Y = bounds.GetTop() - referenceBounds.GetTop();
                break;
            case LeftBottom:
            case RightBottom:
            case CenterBottom:
                offset.Y = referenceBounds.GetBottom() - bounds.GetBottom();
                break;
            case LeftMiddle:
            case RightMiddle:
            case Center:
                offset.Y = bounds.GetMiddle() - referenceBounds.GetMiddle();
                break;
        }

        SetOffset(offset);
        SetSize(Vector2(bounds.Width, bounds.Height));

        return true;
    }

    RectF UIAlignedFrame::ComputeBounds(UIVisualVisitor& visitor, Vector2 desiredSize)
    {
        const RectF referenceBounds = visitor.GetCurrentBounds();
        if (boundsChanged || lastReferenceBounds != referenceBounds || lastDesiredSize != desiredSize)
        {
            RectF bounds = RectF(0.0f, 0.0f, size.X, size.Y);
            if (desiredSize.X >= 0.0f)
                bounds.Width = desiredSize.X;
            if (desiredSize.Y >= 0.0f)
                bounds.Height = desiredSize.Y;

            switch (GetAlign())
            {
                case LeftTop:
                case LeftBottom:
                case LeftMiddle:
                    bounds.X = referenceBounds.GetLeft() + offset.X;
                    break;
                case RightTop:
                case RightBottom:
                case RightMiddle:
                    bounds.X = referenceBounds.GetRight() - offset.X - bounds.Width;
                    break;
                case CenterTop:
                case CenterBottom:
                case Center:
                    bounds.X = referenceBounds.X + ((referenceBounds.Width - bounds.Width) / 2.0f) + offset.X;
                    break;
            }

            switch (GetAlign())
            {
                case LeftTop:
                case RightTop:
                case CenterTop:
                    bounds.Y = referenceBounds.GetTop() + offset.Y;
                    break;
                case LeftBottom:
                case RightBottom:
                case CenterBottom:
                    bounds.Y = referenceBounds.GetBottom() - offset.Y - bounds.Height;
                    break;
                case LeftMiddle:
                case RightMiddle:
                case Center:
                    bounds.Y = referenceBounds.Y + ((referenceBounds.Height - bounds.Height) / 2.0f) + offset.Y;
                    break;
            }

            lastBounds = bounds;
            lastReferenceBounds = referenceBounds;
            lastDesiredSize = desiredSize;
            boundsChanged = false;
        }

        return lastBounds;
    }

    void UIAlignedFrame::Move(Vector2 displacement)
    {
        if (displacement == Vector2::Zero)
            return;

        switch (align)
        {
            case LeftTop:
            case LeftMiddle:
            case CenterTop:
            case Center:
                offset.X += displacement.X;
                offset.Y += displacement.Y;
                break;
            case LeftBottom:
            case CenterBottom:
                offset.X += displacement.X;
                offset.Y -= displacement.Y;
                break;
            case RightTop:
            case RightMiddle:
                offset.X -= displacement.X;
                offset.Y += displacement.Y;
                break;
            case RightBottom:
                offset.X -= displacement.X;
                offset.Y -= displacement.Y;
                break;
        }

        boundsChanged = true;
    }

    bool UIAlignedFrame::IsMovable() const
    {
        return true;
    }

    void UIAlignedFrame::Resize(float left, float top, float right, float bottom)
    {
        if (left == 0.0f && top == 0.0f && right == 0.0f && bottom == 0.0f)
            return;

        size.X += left + right;
        size.Y += top + bottom;

        switch(align)
        {
            case LeftTop:
            case LeftBottom:
            case LeftMiddle:
                offset.X -= left;
                break;
            case RightTop:
            case RightBottom:
            case RightMiddle:
                offset.X -= right;
                break;
            case CenterTop:
            case CenterBottom:
            case Center:
                offset.X -= left * 0.5f;
                offset.X += right * 0.5f;
                break;
        }

        switch(align)
        {
            case LeftTop:
            case RightTop:
            case CenterTop:
                offset.Y -= top;
                break;
            case LeftBottom:
            case RightBottom:
            case CenterBottom:
                offset.Y -= bottom;
                break;
            case LeftMiddle:
            case RightMiddle:
            case Center:
                offset.Y -= top * 0.5f;
                offset.Y += bottom * 0.5f;
                break;
        }

        boundsChanged = true;
    }

    void UIAlignedFrame::ResizeTo(Vector2 size)
    {
        SetSize(size);
    }

    bool UIAlignedFrame::IsResizable() const
    {
        return true;
    }

    void UIAlignedFrame::SetAlign(Alignment value)
    {
        if (align != value)
        {
            align = value;
            boundsChanged = true;
        }
    }

    void UIAlignedFrame::SetOffset(Vector2 value)
    {
        if (offset != value)
        {
            offset = value;
            boundsChanged = true;
        }
    }

    void UIAlignedFrame::SetSize(Vector2 value)
    {
        if (size != value)
        {
            size = value;
            boundsChanged = true;
        }
    }

    void UIAlignedFrame::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        align = static_cast<Alignment>(reader.ReadByte());
        offset = reader.ReadVector2();
        size = reader.ReadVector2();
        boundsChanged = true;
    }

    void UIAlignedFrame::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const UIAlignedFrame* o = static_cast<const UIAlignedFrame*>(original);
        align = o->align;
        offset = o->offset;
        size = o->size;
        boundsChanged = true;
    }
}