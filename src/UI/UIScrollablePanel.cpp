#include <Bibim/Config.h>
#include <Bibim/UIScrollablePanel.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Math.h>
#include <Bibim/UIMouseButtonEventArgs.h>
#include <Bibim/UIMouseEventDispatcher.h>
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

        const Point2 mousePosition = args.GetPosition();
        const Point2 mousePositionDelta = mousePosition - lastMousePosition;
        
        lastMousePosition = args.GetPosition();

        content->SetX(content->GetX() + mousePositionDelta.X);
        content->SetY(content->GetY() + mousePositionDelta.Y);

        // 어느 정도 스크롤이 되었다면 자기 자신을 캡쳐하도록 수정합니다.
        const Point2 mousePositionDeltaFromStart = mousePosition - startMousePosition;
        if (Math::Abs(mousePositionDeltaFromStart.X) > 8 ||
            Math::Abs(mousePositionDeltaFromStart.Y) > 8) // 그냥 경험에 의해 정해진 값
        {
            if (args.GetDispatcher())
                args.GetDispatcher()->SetCapture(this);
        }

        return true;
    }

    bool UIScrollablePanel::OnMouseButtonDown(const UIMouseButtonEventArgs& args)
    {
        if (args.GetButtonCode() == Key::MouseLeftButton)
        {
            isScrolling = true;
            startMousePosition = args.GetPosition(); 
            lastMousePosition = startMousePosition;
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
        const RectF contentBounds = content->ComputeBounds(context.GetCurrentBounds());

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