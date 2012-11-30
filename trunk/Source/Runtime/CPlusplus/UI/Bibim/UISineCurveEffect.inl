namespace Bibim
{
    float UISineCurveEffect::GetAmplitude() const
    {
        return amplitude;
    }

    float UISineCurveEffect::GetOffset() const
    {
        return offset;
    }

    float UISineCurveEffect::GetLength() const
    {
        return length;
    }

    UISineCurveEffect::Form UISineCurveEffect::GetForm() const
    {
        return form;
    }

    const char* UISineCurveEffect::GetFormAsChars() const
    {
        return ConvertFromFormToString(GetForm());
    }

    void UISineCurveEffect::SetFormByChars(const char* value)
    {
        SetForm(ConvertFromStringToForm(value));
    }
}