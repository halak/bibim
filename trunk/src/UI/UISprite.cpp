#include <Bibim/Config.h>
#include <Bibim/UISprite.h>
#include <Bibim/Assert.h>
#include <Bibim/Color.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Sprite.h>
#include <Bibim/Timeline.h>
#include <Bibim/UIDrawingContext.h>
#include <Bibim/UIPickingContext.h>

namespace Bibim
{
    BBImplementsComponent(UISprite);

    UISprite::UISprite()
        : source(nullptr),
          speed(1.0f),
          time(0.0f),
          frameIndex(0),
          horizontalFlip(false),
          verticalFlip(false),
          timeline(nullptr)
    {
        SetSize(1.0f, 1.0f);
        SetSizeMode(ContentSize, ContentSize);
        updater.Owner = this;
    }

    UISprite::~UISprite()
    {
    }

    void UISprite::Update(float dt, int /*timestamp*/)
    {
        if (source == nullptr)
            return;

        time += dt * speed;
        frameIndex = source->GetKeyframeIndex(time, frameIndex);
    }

    const Sprite::Keyframe* UISprite::GetCurrentFrame() const
    {
        return source ? source->GetKeyframeAt(frameIndex) : nullptr;
    }

    void UISprite::SetSource(Sprite* value)
    {
        if (source != value)
        {
            source = value;
            time = 0.0f;
            frameIndex = 0;
        }
    }

    void UISprite::SetSpeed(float value)
    {
        speed = value;
    }

    void UISprite::SetTime(float value)
    {
        if (time != value)
        {
            time = value;
        }
    }

    void UISprite::SetFrameIndex(int value)
    {
        if (frameIndex != value)
        {
            frameIndex = value;
        }
    }

    void UISprite::SetTimeline(Timeline* value)
    {
        if (timeline != value)
        {
            if (timeline)
                timeline->Remove(&updater);

            timeline = value;

            if (timeline)
                timeline->Add(&updater, this);
        }
    }

    Vector2 UISprite::GetContentSize()
    {
        if (const Sprite::Keyframe* kf = GetCurrentFrame())
            return Vector2(kf->GetWidth(), kf->GetHeight());
        else
            return Vector2::Zero;
    }

    void UISprite::OnDraw(UIDrawingContext& context)
    {
        UIVisual::OnDraw(context);

        if (GetSource() == nullptr)
            return;

        if (const Sprite::Keyframe* kf = GetCurrentFrame())
        {
            Image image(kf->Texture, kf->NormalizedClippingRect, kf->AppliedTransform);
            context.Draw(&image, GetHorizontalFlip(), GetVerticalFlip());
        }
    }

    void UISprite::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        source = static_cast<Sprite*>(reader.ReadAsset());
        speed = reader.ReadFloat();
        time = 0.0f;
        frameIndex = 0;
        horizontalFlip = reader.ReadBool();
        verticalFlip = reader.ReadBool();
    }

    void UISprite::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        source = o->source;
        time = o->time;
        frameIndex = o->frameIndex;
        horizontalFlip = o->horizontalFlip;
        verticalFlip = o->verticalFlip;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UISprite::Updater::~Updater()
    {
    }

    void UISprite::Updater::Update(float dt, int timestamp)
    {
        Owner->Update(dt, timestamp);
    }
}