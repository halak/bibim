#include <Bibim/PCH.h>
#include <Bibim/OscillationCurve.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Math.h>

namespace Bibim
{
    BBImplementsComponent(OscillationCurve);

    OscillationCurve::OscillationCurve()
        : mode(Still),
          frequency(4),
          frequencyFloat(4.0f),
          strength(0.0f)
    {
    }

    OscillationCurve::OscillationCurve(OscillationMode mode, int frequency, float strength)
        : mode(mode),
          frequency(Math::Max(frequency, 0)),
          frequencyFloat(static_cast<float>(frequency)),
          strength(strength)
    {
    }

    OscillationCurve::~OscillationCurve()
    {
    }

    float OscillationCurve::Ease(float t) const
    {
        const float sineCurve = Math::Sin(Math::Pi * frequencyFloat * t);
        switch (mode)
        {
            case Still:
                return 0.5f + (0.5f * sineCurve);
            case Crescendo:
                return 0.5f + (0.3f * Math::Exp(+strength * t) * sineCurve);
            case Decrescendo:
                return 0.5f + (0.3f * Math::Exp(-strength * t) * sineCurve);
            case PitchAndRoll:
                return 0.5f + (0.3f * Math::Exp(0.5f * Math::Sin(strength * t)) * sineCurve);
            default:
                BBBreak();
                return t;
        }
    }

    void OscillationCurve::SetFrequency(int value)
    {
        frequency = Math::Max(value, 0);
        frequencyFloat = static_cast<float>(frequency);
    }

    void OscillationCurve::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        mode = static_cast<OscillationMode>(reader.ReadByte());
        frequency = static_cast<int>(reader.ReadShortInt());
        frequencyFloat = static_cast<float>(frequency);
        strength = reader.ReadFloat();
    }

    void OscillationCurve::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        mode = o->mode;
        frequency = o->frequency;
        frequencyFloat = o->frequencyFloat;
        strength = o->strength;
    }
}