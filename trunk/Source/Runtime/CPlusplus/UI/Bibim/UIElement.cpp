#include <Bibim/PCH.h>
#include <Bibim/UIElement.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    UIElement::UIElement()
    {
    }

    UIElement::~UIElement()
    {
    }

    void UIElement::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        name = reader.ReadString();
    }

    void UIElement::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const UIElement*>(original);
        name = o->name;
    }
}