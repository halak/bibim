namespace Bibim
{
    Image* UIMaskEffect::MaskEffector::GetMask() const
    {
        return mask;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Image* UIMaskEffect::GetMask() const
    {
        return mask;
    }
}