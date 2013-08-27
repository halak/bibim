#include <Bibim/Config.h>
#include <Bibim/UIEllipse.h>
#include <Bibim/UIDrawingContext.h>

namespace Bibim
{
    BBImplementsComponent(UIEllipse);

    UIEllipse::UIEllipse()
    {
    }

    UIEllipse::~UIEllipse()
    {
    }

    void UIEllipse::FillShape(UIDrawingContext& context, const RectF& clippedBounds, const RectF& /*bounds*/, Color color)
    {
        context.FillEllipse(clippedBounds, color);
    }

    void UIEllipse::DrawShape(UIDrawingContext& context, const RectF& clippedBounds, const RectF& /*bounds*/, Color color)
    {
        context.DrawEllipse(clippedBounds, color);
    }

    void UIEllipse::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void UIEllipse::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
    }
}