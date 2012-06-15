#include <Bibim/PCH.h>
#include <Bibim/ElasticEasingCurves.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    ElasticEasingCurve::ElasticEasingCurve()
        : amplitude(0.0f),
          period(0.0f)
    {
    }

    ElasticEasingCurve::ElasticEasingCurve(float amplitude, float period)
        : amplitude(amplitude),
          period(period)
    {
    }

    ElasticEasingCurve::~ElasticEasingCurve()
    {
    }

    void ElasticEasingCurve::SetAmplitude(float value)
    {
        amplitude = value;
    }

    void ElasticEasingCurve::SetPeriod(float value)
    {
        period = value;
    }

    void ElasticEasingCurve::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        amplitude = reader.ReadFloat();
        period = reader.ReadFloat();
    }

    void ElasticEasingCurve::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        amplitude = o->amplitude;
        period = o->period;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    BBImplementsComponent(EaseInElasticCurve);

    EaseInElasticCurve::EaseInElasticCurve()
    {
    }

    EaseInElasticCurve::EaseInElasticCurve(float amplitude, float period)
        : Base(amplitude, period)
    {
    }

    EaseInElasticCurve::~EaseInElasticCurve()
    {
    }

    void EaseInElasticCurve::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void EaseInElasticCurve::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    BBImplementsComponent(EaseOutElasticCurve);

    EaseOutElasticCurve::EaseOutElasticCurve()
    {
    }

    EaseOutElasticCurve::EaseOutElasticCurve(float amplitude, float period)
        : Base(amplitude, period)
    {
    }

    EaseOutElasticCurve::~EaseOutElasticCurve()
    {
    }

    void EaseOutElasticCurve::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void EaseOutElasticCurve::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    BBImplementsComponent(EaseInOutElasticCurve);

    EaseInOutElasticCurve::EaseInOutElasticCurve()
    {
    }

    EaseInOutElasticCurve::EaseInOutElasticCurve(float amplitude, float period)
        : Base(amplitude, period)
    {
    }

    EaseInOutElasticCurve::~EaseInOutElasticCurve()
    {
    }

    void EaseInOutElasticCurve::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void EaseInOutElasticCurve::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
    }
}