#include <Bibim/PCH.h>
#include <Bibim/UISineCurveEffect.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    BBImplementsComponent(UISineCurveEffect);

    UISineCurveEffect::UISineCurveEffect()
    {
    }

    UISineCurveEffect::~UISineCurveEffect()
    {
    }

    void UISineCurveEffect::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void UISineCurveEffect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        /*const This* o = static_cast<const This*>(original);*/
    }
}