#include <Bibim/PCH.h>
#include <Bibim/UIOpacityMaskEffect.h>

namespace Bibim
{
    BBImplementsComponent(UIOpacityMaskEffect);

    UIOpacityMaskEffect::UIOpacityMaskEffect()
        : Base(ClassIndex, true, true)
    {
    }

    UIOpacityMaskEffect::~UIOpacityMaskEffect()
    {
    }

    void UIOpacityMaskEffect::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        BBBreak();
    }

    void UIOpacityMaskEffect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        BBBreak();
    }
}