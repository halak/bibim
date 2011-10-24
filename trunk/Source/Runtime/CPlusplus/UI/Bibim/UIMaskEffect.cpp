#include <Bibim/PCH.h>
#include <Bibim/UIMaskEffect.h>

namespace Bibim
{
    UIMaskEffect::UIMaskEffect()
    {
    }

    UIMaskEffect::~UIMaskEffect()
    {
    }

    void UIMaskEffect::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        BBBreak();
    }

    void UIMaskEffect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        BBBreak();
    }
}