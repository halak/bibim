#include <Bibim/UIEffectMap.h>

namespace Bibim
{
    UIEffectMap::UIEffectMap()
    {
    }

    UIEffectMap::~UIEffectMap()
    {
    }

    UIElement* UIEffectMap::Create(StreamReader& /*reader*/, UIElement* /*existingInstance*/)
    {
        return nullptr;
    }
}