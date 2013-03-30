namespace Bibim
{
    UIGeometryEffect* UIEffectMap::GetGeometryEffect() const
    {
        return geomEffect;
    }

    const UIEffectMap::PixelEffectCollection& UIEffectMap::GetPixelEffects() const
    {
        return pixelEffects;
    }
}