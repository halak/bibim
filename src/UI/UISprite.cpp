#include <Bibim/Config.h>
#include <Bibim/UISprite.h>
#include <Bibim/Assert.h>
#include <Bibim/Color.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Math.h>
#include <Bibim/Sprite.h>
#include <Bibim/Timeline.h>
#include <Bibim/UIDrawingContext.h>
#include <Bibim/UIWindow.h>
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
          autoRemove(true),
          timeline(nullptr)
    {
        SetSize(1.0f, 1.0f);
        SetSizeMode(ContentSize, ContentSize);
        updater.Owner = this;
    }

    UISprite::~UISprite()
    {
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
            UpdateOrigin();
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

    void UISprite::OnStep(float dt, int /*timestamp*/)
    {
        if (source == nullptr)
            return;

        if (source->GetLooped() == false && 
            time == source->GetDuration())
        {
            if (GetAutoRemove())
            {
                UIPanel* parent = GetParent();
                if (parent && parent->IsWindow())
                    static_cast<UIWindow*>(parent)->RemoveChild(this);
            }
        }

        time += dt * speed;

        if (source->GetLooped())
            time = Math::Mod(time, source->GetDuration());
        else
            time = Math::Min(time, source->GetDuration());

        if (time < source->GetDuration())
        {
            if (speed >= 0.0f)
                frameIndex = source->GetKeyframeIndex(time, frameIndex);
            else
                frameIndex = source->GetKeyframeIndex(time);
        }
        else
            frameIndex = source->GetKeyframes().size() - 1;

        UpdateOrigin();
    }

    void UISprite::UpdateOrigin()
    {
        if (const Sprite::Keyframe* kf = GetCurrentFrame())
            SetOrigin(Vector2(kf->Origin.X / kf->GetWidth(), kf->Origin.Y / kf->GetHeight()));
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
        Owner->OnStep(dt, timestamp);
    }
}