#include <Bibim/Config.h>
#include <Bibim/UIRect.h>
#include <Bibim/UIDrawingContext.h>

namespace Bibim
{
    BBImplementsComponent(UIRect);

    UIRect::UIRect()
    {
    }

    UIRect::~UIRect()
    {
    }

    void UIRect::FillShape(UIDrawingContext& context, const RectF& clippedBounds, const RectF& /*bounds*/, Color color)
    {
        context.FillRect(clippedBounds, color);
    }

    void UIRect::DrawShape(UIDrawingContext& context, const RectF& clippedBounds, const RectF& /*bounds*/, Color color)
    {
        context.DrawRect(clippedBounds, color);
    }

    void UIRect::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void UIRect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
    }
}