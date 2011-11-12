#include <Bibim/PCH.h>
#include <Bibim/UIElement.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    const int UIElement::UnspecifiedID = -1;

    UIElement::UIElement()
        : id(UnspecifiedID)
    {
    }

    UIElement::~UIElement()
    {
    }

    void UIElement::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        id = reader.ReadInt();
        name = reader.ReadString();
    }

    void UIElement::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const UIElement*>(original);
        id = o->id;
        name = o->name;
    }
}