#include <Bibim/PCH.h>
#include <Bibim/UIMaskEffect.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Image.h>

namespace Bibim
{
    UIMaskEffect::UIMaskEffect(bool isFixedFunctionImplemented, bool isShaderFunctionImplemented, Image* mask)
        : Base(ClassIndex, isFixedFunctionImplemented, isShaderFunctionImplemented),
          mask(mask)
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

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIMaskEffect::MaskEffector::MaskEffector(UIMaskEffect* effect)
        : UIRenderer::Effector(true),
          mask(effect->mask)
    {
    }

    UIMaskEffect::MaskEffector::MaskEffector(int shaderEffectNameHint, UIMaskEffect* effect)
        : UIRenderer::Effector(shaderEffectNameHint, true),
          mask(effect->mask)
    {
    }

    UIMaskEffect::MaskEffector::~MaskEffector()
    {
    }
}