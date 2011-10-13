#include <Bibim/PCH.h>
#include <Bibim/UIEffect.h>

namespace Bibim
{
    UIEffect::UIEffect()
    {
    }

    UIEffect::~UIEffect()
    {
    }

    void UIEffect::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void UIEffect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
    }
}