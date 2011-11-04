#include <Bibim/PCH.h>
#include <Bibim/UIPixelEffect.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    UIPixelEffect::UIPixelEffect(int slotIndex, bool isFixedFunctionImplemented, bool isShaderFunctionImplemented)
        : slotIndex(slotIndex),
          isFixedFunctionImplemented(isFixedFunctionImplemented),
          isShaderFunctionImplemented(isShaderFunctionImplemented)
    {
    }

    UIPixelEffect::~UIPixelEffect()
    {
    }

    void UIPixelEffect::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void UIPixelEffect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const UIPixelEffect* o = static_cast<const UIPixelEffect*>(original);
        BBAssert(slotIndex == o->slotIndex);
        BBAssert(isFixedFunctionImplemented == o->isFixedFunctionImplemented);
        BBAssert(isShaderFunctionImplemented == o->isShaderFunctionImplemented);
    }
}