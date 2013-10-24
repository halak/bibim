#include <Bibim/Config.h>
#include <Bibim/UICCParticleSystem.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/CCParticleEmitter.h>
#include <Bibim/CCParticleSystem.h>
#include <Bibim/Timeline.h>
#include <Bibim/UIDrawingContext.h>

namespace Bibim
{
    BBImplementsComponent(UICCParticleSystem);

    UICCParticleSystem::UICCParticleSystem()
        : emitter(nullptr),
          source(nullptr),
          timeline(nullptr)
    {
        updater.o = this;
        SetSize(1.0f, 1.0f);
        SetSizeMode(ContentSize, ContentSize);
    }

    UICCParticleSystem::~UICCParticleSystem()
    {
        SetTimeline(nullptr);
        SetSource(nullptr);
    }

    void UICCParticleSystem::SetSource(CCParticleSystem* value)
    {
        if (source != value)
        {
            source = value;

            delete emitter;

            if (source)
                emitter = new CCParticleEmitter(source);
            else
                emitter = nullptr;
        }
    }

    void UICCParticleSystem::SetTimeline(Timeline* value)
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

    Vector2 UICCParticleSystem::GetContentSize()
    {
        if (source)
            return Vector2(16.0f, 16.0f);
        else
            return Vector2::Zero;
    }

    void UICCParticleSystem::OnStep(float dt, int timestamp)
    {
        if (emitter)
            emitter->Update(dt, timestamp);
    }

    void UICCParticleSystem::OnDraw(UIDrawingContext& context)
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

    void UICCParticleSystem::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        SetSource(static_cast<CCParticleSystem*>(reader.ReadAsset()));
    }

    void UICCParticleSystem::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        SetSource(o->source);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UICCParticleSystem::Updater::Updater()
        : o(nullptr)
    {
    }

    UICCParticleSystem::Updater::~Updater()
    {
    }

    void UICCParticleSystem::Updater::Update(float dt, int timestamp)
    {
        o->OnStep(dt, timestamp);
    }
}