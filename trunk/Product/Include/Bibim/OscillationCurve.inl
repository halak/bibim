namespace Bibim
{
    OscillationCurve::OscillationMode OscillationCurve::GetMode() const
    {
        return mode;
    }

    void OscillationCurve::SetMode(OscillationMode value)
    {
        mode = value;
    }

    int OscillationCurve::GetFrequency() const
    {
        return frequency;
    }

    float OscillationCurve::GetStrength() const
    {
        return strength;
    }

    void OscillationCurve::SetStrength(float value)
    {
        strength = value;
    }
}