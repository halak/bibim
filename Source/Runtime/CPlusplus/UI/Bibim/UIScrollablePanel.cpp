#include <Bibim/PCH.h>
#include <Bibim/UIScrollablePanel.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Math.h>
#include <Bibim/UIMouseButtonEventArgs.h>
#include <Bibim/UIDrawingContext.h>
#include <Bibim/UIPickingContext.h>
#include <Bibim/UIVisual.h>

namespace Bibim
{
    BBImplementsComponent(UIScrollablePanel);

    UIScrollablePanel::UIScrollablePanel()
        : isScrolling(false)
    {
        SetFocusable(true);
    }

    UIScrollablePanel::~UIScrollablePanel()
    {
    }

    void UIScrollablePanel::SetContent(UIVisual* value)
    {
        if (content != value)
        {
            if (content)
                Remove(content);

            content = value;

            if (content)
                Add(content);
        }
    }

    void UIScrollablePanel::OnDraw(UIDrawingContext& context)
    {
        RestrictContent(context);
        Base::OnDraw(context);
    }

    void UIScrollablePanel::OnPick(UIPickingContext& context)
    {
        RestrictContent(context);
        Base::OnPick(context);
    }

    bool UIScrollablePanel::OnMouseMove(const UIMouseEventArgs& args)
    {
        if (content == nullptr ||
            isScrolling == false)
            return false;

        BBAssert(content->GetXMode() == UIVisual::AbsolutePosition &&
                 content->GetYMode() == UIVisual::AbsolutePosition);

        const Point2 mousePositionDelta = args.GetPosition() - lastMousePosition;
        
        lastMousePosition = args.GetPosition();

        content->SetX(content->GetX() + mousePositionDelta.X);
        content->SetY(content->GetY() + mousePositionDelta.Y);

        return true;
    }

    bool UIScrollablePanel::OnMouseButtonDown(const UIMouseButtonEventArgs& args)
    {
        if (args.GetButtonCode() == Key::MouseLeftButton)
        {
            isScrolling = true;
            lastMousePosition = args.GetPosition();
            return true;
        }
        else
            return false;
    }

    bool UIScrollablePanel::OnMouseButtonUp(const UIMouseButtonEventArgs& args)
    {
        if (args.GetButtonCode() == Key::MouseLeftButton)
        {
            isScrolling = false;
            return true;
        }
        else
            return false;
    }

    void UIScrollablePanel::RestrictContent(UIVisualVisitor& context)
    {
        if (content == nullptr)
            return;

        BBAssert(content->GetAnchorPoint() == UIVisual::LeftTop);
        BBAssertDebug(content->GetParent() == this); // 이기 때문에 content->ComputeBounds에서 올바른 값을 반환할 수 있습니다.

        const RectF bounds = context.GetCurrentBounds();
        const RectF contentBounds = content->ComputeBounds(context);

        const float cx = Math::Clamp(contentBounds.X - bounds.X, -Math::Max(contentBounds.Width  - bounds.Width, 0.0f),  0.0f);
        const float cy = Math::Clamp(contentBounds.Y - bounds.Y, -Math::Max(contentBounds.Height - bounds.Height, 0.0f), 0.0f);
        content->SetX(cx);
        content->SetY(cy);
    }

    void UIScrollablePanel::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        content = static_cast<UIVisual*>(reader.ReadComponent());
    }

    void UIScrollablePanel::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        content = context.Clone(o->content);
    }
}