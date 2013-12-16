#include <Bibim/Config.h>
#include <Bibim/UITrail.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/CCParticleEmitter.h>
#include <Bibim/CCParticleSystem.h>
#include <Bibim/Timeline.h>
#include <Bibim/UIDrawingContext.h>
#include <Bibim/UIWindow.h>

namespace Bibim
{
    BBImplementsComponent(UITrail);

    UITrail::UITrail()
        : globalAngle(0.0f),
          emitter(nullptr),
          source(nullptr),
          timeline(nullptr)
    {
        updater.o = this;
        SetSize(1.0f, 1.0f);
        SetSizeMode(ContentSize, ContentSize);
    }

    UITrail::~UITrail()
    {
        SetTimeline(nullptr);
        SetSource(nullptr);
    }

    float UITrail::GetGlobalAngle() const
    {
        return globalAngle;
    }

    void UITrail::SetGlobalAngle(float value)
    {
        globalAngle = value;

        if (emitter)
            emitter->SetGlobalAngle(globalAngle);
    }

    void UITrail::SetSource(CCParticleSystem* value)
    {
        if (source != value)
        {
            source = value;

            delete emitter;

            if (source)
            {
                emitter = new CCParticleEmitter(source);
                emitter->SetGlobalAngle(globalAngle);
            }
            else
                emitter = nullptr;
        }
    }

    void UITrail::SetTimeline(Timeline* value)
    {
        if (timeline != value)
        {
            if (timeline)
                timeline->Remove(&updater);

            timeline = value;

            if (timeline)
                timeline->Add(&updater);
        }
    }

    Vector2 UITrail::GetContentSize()
    {
        if (source)
            return Vector2(16.0f, 16.0f);
        else
            return Vector2::Zero;
    }

    void UITrail::OnStep(float dt, int timestamp)
    {
        if (emitter)
        {
            if (emitter->Update(dt, timestamp) == false)
            {
                UIPanel* parent = GetParent();
                if (parent && parent->IsWindow())
                    static_cast<UIWindow*>(parent)->RemoveChild(this);
            }
        }
    }

    void UITrail::OnDraw(UIDrawingContext& context)
    {
        UIVisual::OnDraw(context);

        if (emitter == nullptr)
            return;

        const Vector2 centerPoint = context.GetCurrentBounds().GetCenterPoint();

        const CCParticle* particles = emitter->GetParticles();
        const int count = emitter->GetNumberOfParticles();
        Image* image = source->GetImage();

        for (int i = 0; i < count; i++)
        {
            const CCParticle& p = particles[i];
            context.DrawUnclipped(centerPoint + p.pos, p.rotation, p.size, image, Color(p.color));
        }
    }

    void UITrail::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        SetSource(static_cast<CCParticleSystem*>(reader.ReadAsset()));
    }

    void UITrail::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        globalAngle = o->globalAngle;
        SetSource(o->source);
        SetTimeline(o->timeline);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UITrail::Updater::Updater()
        : o(nullptr)
    {
    }

    UITrail::Updater::~Updater()
    {
    }

    void UITrail::Updater::Update(float dt, int timestamp)
    {
        o->OnStep(dt, timestamp);
    }
}