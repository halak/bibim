#include <Bibim/PCH.h>
#include <Bibim/EvalTimeflow.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Math.h>

namespace Bibim
{
    BBImplementsComponent(EvalTimeflow);

    EvalTimeflow::EvalTimeflow()
        : time(0.0f),
          duration(0.0f),
          velocity(1.0f),
          looped(true)
    {
    }

    EvalTimeflow::~EvalTimeflow()
    {
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
            if (nextTime < duration)
            {
                if (looped && duration > 0.0f)
                    time = Math::Mod(nextTime, duration);
                else
                    time = duration;
            }
            else
            {
                BBAssertDebug(nextTime < 0.0f);
                if (looped && duration > 0.0f)
                    time = duration - Math::Mod(-nextTime, duration);
                else
                    time = 0.0f;
            }
        }
    }

    void EvalTimeflow::Reset()
    {
        time = 0.0f;
    }

    float EvalTimeflow::Evaluate(EvalContext& /*context*/)
    {
        return time;
    }

    void EvalTimeflow::SetDuration(float value)
    {
        value = Math::Max(value, 0.0f);
    }

    void EvalTimeflow::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        time = 0.0f;
        duration = reader.ReadFloat();
        velocity = reader.ReadFloat();
        looped = reader.ReadBool();
    }

    void EvalTimeflow::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        time = o->time;
        duration = o->duration;
        velocity = o->velocity;
        looped = o->looped;
    }
}