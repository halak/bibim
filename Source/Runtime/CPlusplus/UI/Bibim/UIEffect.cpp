#include <Bibim/PCH.h>
#include <Bibim/UIEffect.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    UIEffect::UIEffect(int slotIndex)
        : slotIndex(slotIndex)
    {
    }

    UIEffect::~UIEffect()
    {
    }

    void UIEffect::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        slotIndex = static_cast<int>(reader.ReadInt16());
    }

    void UIEffect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        slotIndex = o->slotIndex;
    }
}