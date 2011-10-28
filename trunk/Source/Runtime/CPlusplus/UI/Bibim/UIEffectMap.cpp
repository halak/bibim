#include <Bibim/PCH.h>
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
        BBBreak();
    }

    void UIEffectMap::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        BBBreak();
    }
}