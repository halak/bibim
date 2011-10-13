#include <Bibim/UIEffectMap.h>

namespace Bibim
{
    BBImplementsComponent(UIEffectMap);

    UIEffectMap::UIEffectMap()
    {
    }

    UIEffectMap::~UIEffectMap()
    {
    }

    void UIEffectMap::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        BBAssert(0);
    }

    void UIEffectMap::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        BBAssert(0);
    }
}