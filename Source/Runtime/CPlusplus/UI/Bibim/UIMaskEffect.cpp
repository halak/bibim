#include <Bibim/PCH.h>
#include <Bibim/UIMaskEffect.h>

namespace Bibim
{
    UIMaskEffect::UIMaskEffect(int slotIndex)
        : Base(slotIndex)
    {
    }

    UIMaskEffect::~UIMaskEffect()
    {
    }

    void UIMaskEffect::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void UIMaskEffect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
    }
}