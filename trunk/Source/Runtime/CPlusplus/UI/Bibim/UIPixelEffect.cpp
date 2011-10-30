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
        slotIndex = static_cast<int>(reader.ReadInt16());
        isFixedFunctionImplemented = reader.ReadBool();
        isShaderFunctionImplemented = reader.ReadBool();
    }

    void UIPixelEffect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        slotIndex = o->slotIndex;
        isFixedFunctionImplemented = o->isFixedFunctionImplemented;
        isShaderFunctionImplemented = o->isShaderFunctionImplemented;
    }
}