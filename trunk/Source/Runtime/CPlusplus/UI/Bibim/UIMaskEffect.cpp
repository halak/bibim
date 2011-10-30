#include <Bibim/PCH.h>
#include <Bibim/UIMaskEffect.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Image.h>

namespace Bibim
{
    UIMaskEffect::UIMaskEffect(int slotIndex, bool isFixedFunctionImplemented, bool isShaderFunctionImplemented)
        : Base(slotIndex, isFixedFunctionImplemented, isShaderFunctionImplemented)
    {
    }

    UIMaskEffect::~UIMaskEffect()
    {
    }

    void UIMaskEffect::SetMask(Image* value)
    {
        mask = value;
    }

    void UIMaskEffect::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        mask = static_cast<GameAsset*>(reader.ReadAsset());
    }

    void UIMaskEffect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        mask = o->mask;
    }
}