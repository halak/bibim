#include <Bibim/Config.h>
#include <Bibim/UIShape.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/UIDrawingContext.h>

namespace Bibim
{
    UIShape::UIShape()
        : fillColor(0, 0, 0),
          lineColor(0, 0, 0, 0)
    {
    }

    UIShape::~UIShape()
    {
    }

    void UIShape::OnDraw(UIDrawingContext& context)
    {
        UIVisual::OnDraw(context);

        const RectF clippedBounds = context.GetCurrentClippedBounds();
        const RectF bounds = context.GetCurrentBounds();

        if (fillColor.A > 0)
            FillShape(context, clippedBounds, bounds, fillColor);
        if (lineColor.A > 0)
            DrawShape(context, clippedBounds, bounds, lineColor);
    }

    void UIShape::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        fillColor = reader.ReadColor();
        lineColor = reader.ReadColor();
    }

    void UIShape::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        fillColor = o->fillColor;
        lineColor = o->lineColor;
    }
}