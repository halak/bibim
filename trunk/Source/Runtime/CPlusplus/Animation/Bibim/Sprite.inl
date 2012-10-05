namespace Bibim
{
    int Sprite::GetKeyframeIndex(float time) const
    {
        return GetKeyframeIndex(time, 0);
    }

    const Sprite::Keyframe* Sprite::GetKeyframeAt(int index) const
    {
        if (0 <= index && index < static_cast<int>(keyframes.size()))
            return &keyframes[index];
        else
            return nullptr;
    }

    const Sprite::KeyframeCollection& Sprite::GetKeyframes() const
    {
        return keyframes;
    }

    float Sprite::GetDuration() const
    {
        return duration;
    }

    BlendMode Sprite::GetBlendMode() const
    {
        return blendMode;
    }

    void Sprite::SetBlendMode(BlendMode value)
    {
        blendMode = value;
    }
}