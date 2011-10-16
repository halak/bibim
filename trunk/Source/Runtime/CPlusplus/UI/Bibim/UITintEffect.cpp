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
        BBBreak();
    }

    void UITintEffect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        BBBreak();
    }
}