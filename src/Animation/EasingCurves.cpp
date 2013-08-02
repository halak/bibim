#include <Bibim/Config.h>
#include <Bibim/EasingCurves.h>

namespace Bibim
{
    EasingCurve::EasingCurve()
    {
    }

    EasingCurve::~EasingCurve()
    {
    }

    void EasingCurve::OnRead(Bibim::ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void EasingCurve::OnCopy(const Bibim::GameComponent* original, Bibim::CloningContext& context)
    {
        Base::OnCopy(original, context);
    }

    BBImplementsSingletonComponent(LinearCurve);
    BBImplementsSingletonComponent(EaseInQuadraticCurve);
    BBImplementsSingletonComponent(EaseOutQuadraticCurve);
    BBImplementsSingletonComponent(EaseInOutQuadraticCurve);
    BBImplementsSingletonComponent(EaseInCubicCurve);
    BBImplementsSingletonComponent(EaseOutCubicCurve);
    BBImplementsSingletonComponent(EaseInOutCubicCurve);
    BBImplementsSingletonComponent(EaseInQuarticCurve);   
    BBImplementsSingletonComponent(EaseOutQuarticCurve); 
    BBImplementsSingletonComponent(EaseInOutQuarticCurve);
    BBImplementsSingletonComponent(EaseInQuinticCurve);   
    BBImplementsSingletonComponent(EaseOutQuinticCurve); 
    BBImplementsSingletonComponent(EaseInOutQuinticCurve); 
    BBImplementsSingletonComponent(EaseInSinusoidalCurve);
    BBImplementsSingletonComponent(EaseOutSinusoidalCurve);
    BBImplementsSingletonComponent(EaseInOutSinusoidalCurve);
    BBImplementsSingletonComponent(EaseInExponentialCurve);
    BBImplementsSingletonComponent(EaseOutExponentialCurve);
    BBImplementsSingletonComponent(EaseInOutExponentialCurve);
    BBImplementsSingletonComponent(EaseInCircularCurve);
    BBImplementsSingletonComponent(EaseOutCircularCurve);
    BBImplementsSingletonComponent(EaseInOutCircularCurve);
}