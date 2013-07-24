#pragma once
#ifndef __BIBIM_SPRITE_H__
#define __BIBIM_SPRITE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameAsset.h>
#   include <Bibim/BlendMode.h>
#   include <Bibim/Image.h>
#   include <Bibim/Rect.h>
#   include <Bibim/RectF.h>
#   include <Bibim/String.h>
#   include <vector>

    namespace Bibim
    {
        class Sprite : public GameAsset
        {
            BBSerializableAssetClass(Sprite, GameAsset, 'A', 'S', 'P', 'R');
            public:
                struct Keyframe
                {
                    String TextureURI;
                    Rect ClippingRect;
                    RectF NormalizedClippingRect;
                    Image::Transform AppliedTransform;
                    int Width;
                    int Height;
                    Texture2DPtr Texture;
                    Vector2 Origin;
                    float StartTime;
                    float EndTime;
                    float Duration;

                    static const Keyframe Empty;
                };
                typedef std::vector<Keyframe> KeyframeCollection;

            public:
                Sprite();
                virtual ~Sprite();

                int GetKeyframeIndex(float time, int index) const;
                inline int GetKeyframeIndex(float time) const;
                inline const Keyframe* GetKeyframeAt(int index) const;

                inline const KeyframeCollection& GetKeyframes() const;
                inline float GetDuration() const;
                inline BlendMode GetBlendMode() const;
                inline void SetBlendMode(BlendMode value);

            private:
                Sprite(KeyframeCollection& keyframes, float duration, BlendMode blendMode);

            private:
                KeyframeCollection keyframes;
                float duration;
                BlendMode blendMode;
        };
    }

#endif