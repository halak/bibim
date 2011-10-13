#include <Bibim/UITintEffect.h>

namespace Bibim
{
    BBImplementsComponent(UITintEffect);

    UITintEffect::UITintEffect()
    {
    }

    UITintEffect::~UITintEffect()
    {
    }

    void UITintEffect::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        BBAssert(0);
    }

    void UITintEffect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        BBAssert(0);
    }
}