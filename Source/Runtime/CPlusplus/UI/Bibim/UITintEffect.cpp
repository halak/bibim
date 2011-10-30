#include <Bibim/PCH.h>
#include <Bibim/UITintEffect.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    BBImplementsComponent(UITintEffect);

    UITintEffect::UITintEffect()
        : value(1.0f, 1.0f, 1.0f, 0.0f)
    {
    }

    UITintEffect::UITintEffect(Vector4 value)
        : value(value)
    {
    }

    UITintEffect::~UITintEffect()
    {
    }

    void UITintEffect::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        value = reader.ReadVector4();
    }

    void UITintEffect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        value = o->value;
    }
}