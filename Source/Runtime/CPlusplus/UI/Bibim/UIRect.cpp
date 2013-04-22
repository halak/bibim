#include <Bibim/Config.h>
#include <Bibim/UIRect.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/UIDrawingContext.h>

namespace Bibim
{
    BBImplementsComponent(UIRect);

    UIRect::UIRect()
        : fillColor(0, 0, 0)
    {
    }

    UIRect::~UIRect()
    {
    }

    void UIRect::OnDraw(UIDrawingContext& context)
    {
        UIVisual::OnDraw(context);

        context.FillRect(context.GetCurrentClippedBounds(), fillColor);
    }

    void UIRect::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        fillColor = reader.ReadColor();
    }

    void UIRect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        fillColor = o->fillColor;
    }
}