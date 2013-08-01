#include <Bibim/Config.h>
#include <Bibim/EvalTimeflow.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Math.h>
#include <Bibim/Timeline.h>

namespace Bibim
{
    BBImplementsComponent(EvalTimeflow);

    EvalTimeflow::EvalTimeflow()
        : evaluatedTime(0.0f),
          timeline(nullptr),
          time(0.0f),
          duration(0.0f),
          velocity(1.0f),
          stopBehavior(PauseAtStop),
          looped(true),
          normalized(false),
          isUpdating(false)
    {
    }

    EvalTimeflow::~EvalTimeflow()
    {
        if (timeline != nullptr && isUpdating)
            timeline->Remove(this);
    }

    void EvalTimeflow::Update(float dt, int timestamp)
    {
        if (lastTimestamp == timestamp || velocity == 0.0f)
            return;
        else
            lastTimestamp = timestamp;

        const float nextTime = time + (dt * velocity);

        if (0 <= nextTime && nextTime <= duration)
            time = nextTime;
        else
        {
            if (nextTime > duration)
            {
                if (looped && duration > 0.0f)
                    time = Math::Mod(nextTime, duration);
                else
                    time = duration;
            }
            else
            {
                if (looped && duration > 0.0f)
                    time = duration - Math::Mod(-nextTime, duration);
                else
                    time = 0.0f;
            }
        }

        if (normalized)
        {
            if (duration > 0.0f)
                evaluatedTime = time / duration;
            else
                evaluatedTime = 0.0f;
        }
        else
            evaluatedTime = time;
    }

    void EvalTimeflow::Start()
    {
        if (isUpdating)
            return;

        isUpdating = true;
        if (timeline != nullptr)
            timeline->Add(this, this);
    }

    void EvalTimeflow::Stop()
    {
        if (isUpdating == false)
            return;

        isUpdating = false;
        if (timeline != nullptr)
            timeline->Remove(this);

        switch (stopBehavior)
        {
            case PauseAtStop:
                break;
            case ResetAtStop:
                time = 0.0f;
                evaluatedTime = 0.0f;
                break;
            case FinishAtStop:
                time = duration;
                if (normalized)
                    evaluatedTime = 1.0f;
                else
                    evaluatedTime = duration;
                break;
        }
    }

    void EvalTimeflow::Reset()
    {
        time = 0.0f;
        evaluatedTime = 0.0f;
    }

    float EvalTimeflow::Evaluate(EvalContext& /*context*/)
    {
        return evaluatedTime;
    }

    void EvalTimeflow::SetTimeline(Timeline* value)
    {
        if (timeline != value)
        {
            if (timeline != nullptr && isUpdating)
                timeline->Remove(this);

            timeline = value;

            if (timeline != nullptr && isUpdating)
                timeline->Add(this);
        }
    }

    void EvalTimeflow::SetDuration(float value)
    {
        value = Math::Max(value, 0.0f);
    }

    void EvalTimeflow::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        evaluatedTime = 0.0f;
        timeline = static_cast<Timeline*>(reader.ReadModule(Timeline::ClassID));
        time = 0.0f;
        duration = reader.ReadFloat();
        velocity = reader.ReadFloat();
        stopBehavior = static_cast<Behavior>(reader.ReadByte());
        looped = reader.ReadBool();
        normalized = reader.ReadBool();
    }

    void EvalTimeflow::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        evaluatedTime = o->evaluatedTime;
        timeline = o->timeline;
        time = o->time;
        duration = o->duration;
        velocity = o->velocity;
        stopBehavior = o->stopBehavior;
        looped = o->looped;
        normalized = o->normalized;
        isUpdating = o->isUpdating;

        if (timeline != nullptr && isUpdating)
            timeline->Add(this);
    }
}