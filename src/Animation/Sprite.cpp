#include <Bibim/Config.h>
#include <Bibim/Sprite.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/Math.h>
#include <Bibim/Texture2D.h>

namespace Bibim
{
    Sprite::Sprite()
    {
        // for cloning and deserialization
    }

    Sprite::Sprite(KeyframeCollection& keyframes, float duration, BlendMode blendMode, bool looped)
        : duration(duration),
          blendMode(blendMode),
          looped(looped)
    {
        this->keyframes.swap(keyframes);
    }

    Sprite::~Sprite()
    {
    }

    int Sprite::GetKeyframeIndex(float time, int index) const
    {
        time = Math::Mod(time, duration);

        const int count = static_cast<int>(keyframes.size());
        for (int i = index; i < count; i++)
        {
            const Keyframe& kf = keyframes[i];
            if (kf.StartTime <= time && time <= kf.EndTime)
                return i;
        }

        for (int i = 0; i < index; i++)
        {
            const Keyframe& kf = keyframes[i];
            if (kf.StartTime <= time && time <= kf.EndTime)
                return i;
        }

        return -1;
    }

    GameAsset* Sprite::Create(StreamReader& reader, GameAsset* /*existingInstance*/)
    {
        const BlendMode blendMode = static_cast<BlendMode>(reader.ReadByte());
        const bool looped = reader.ReadBool();
        const int numberOfKeyframes = static_cast<int>(reader.ReadShortInt());
        KeyframeCollection keyframes;
        keyframes.reserve(numberOfKeyframes);
        float totalDuration = 0.0f;
        for (int i = 0; i < numberOfKeyframes; i++)
        {
            Keyframe kf;
            kf.TextureURI = reader.ReadString();
            kf.ClippingRect = reader.ReadRect();
            kf.AppliedTransform = static_cast<Image::Transform>(reader.ReadByte());
            kf.Origin = reader.ReadVector2();
            kf.StartTime = totalDuration;
            kf.Duration = reader.ReadFloat();
            kf.EndTime = kf.StartTime + kf.Duration;
            kf.Texture = static_cast<Texture2D*>(reader.GetStorage()->Load(kf.TextureURI));
            kf.NormalizedClippingRect = Image::CalculateNormalizedRect(kf.ClippingRect, kf.Texture);

            totalDuration += kf.Duration;
            keyframes.push_back(kf);
        }

        return new Sprite(keyframes, totalDuration, blendMode, looped);
    }
}