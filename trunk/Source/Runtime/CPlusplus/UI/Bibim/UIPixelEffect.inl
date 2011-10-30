namespace Bibim
{
    int UIPixelEffect::GetSlotIndex() const
    {
        return slotIndex;
    }

    bool UIPixelEffect::IsFixedFunctionImplemented() const
    {
        return isFixedFunctionImplemented;
    }

    bool UIPixelEffect::IsShaderFunctionImplemented() const
    {
        return isShaderFunctionImplemented;
    }
}