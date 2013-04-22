#include <Bibim/Config.h>
#include <Bibim/UIGeometryEffect.h>

namespace Bibim
{
    UIGeometryEffect::UIGeometryEffect()
    {
    }

    UIGeometryEffect::~UIGeometryEffect()
    {
    }

    void UIGeometryEffect::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void UIGeometryEffect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
    }
}