#include <Bibim/Config.h>
#include <Bibim/UIRoundedRect.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/UIDrawingContext.h>

namespace Bibim
{
    BBImplementsComponent(UIRoundedRect);

    UIRoundedRect::UIRoundedRect()
        : leftTop(0.0f),
          rightTop(0.0f),
          leftBottom(0.0f),
          rightBottom(0.0f)
    {
    }
    
    UIRoundedRect::UIRoundedRect(float leftTop, float rightTop, float leftBottom, float rightBottom)
        : leftTop(Math::Max(leftTop, 0.0f)),
          rightTop(Math::Max(rightTop, 0.0f)),
          leftBottom(Math::Max(leftBottom, 0.0f)),
          rightBottom(Math::Max(rightBottom, 0.0f))
    {
    }

    UIRoundedRect::~UIRoundedRect()
    {
    }

    void UIRoundedRect::FillShape(UIDrawingContext& context, const RectF& clippedBounds, const RectF& bounds, Color color)
    {
        context.FillRoundedRect(clippedBounds, leftTop, rightTop, leftBottom, rightBottom, color);
    }

    void UIRoundedRect::DrawShape(UIDrawingContext& context, const RectF& clippedBounds, const RectF& bounds, Color color)
    {
        context.DrawRoundedRect(clippedBounds, leftTop, rightTop, leftBottom, rightBottom, color);
    }

    void UIRoundedRect::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        leftTop = reader.ReadFloat();
        rightTop = reader.ReadFloat();
        leftBottom = reader.ReadFloat();
        rightBottom = reader.ReadFloat();
    }

    void UIRoundedRect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const UIRoundedRect* o = static_cast<const UIRoundedRect*>(original);
        leftTop = o->leftTop;
        rightTop = o->rightTop;
        leftBottom = o->leftBottom;
        rightBottom = o->rightBottom;
    }
}