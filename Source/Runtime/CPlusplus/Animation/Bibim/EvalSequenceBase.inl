#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    template <typename T>
    EvalSequenceBase<T>::EvalSequenceBase()
        : time(0.0f),
          velocity(1.0f),
          looped(false),
          timeChanged(true),
          value(),
          lastTimestamp(0)
    {
    }
    
    template <typename T>
    EvalSequenceBase<T>::~EvalSequenceBase()
    {
    }

    template <typename T>
    void EvalSequenceBase<T>::Update(float dt, int timestamp)
    {
        if (lastTimestamp == timestamp)
            return;
        else
            lastTimestamp = timestamp;

        time += dt;
        timeChanged = true;
    }

    template <typename T>
    T EvalSequenceBase<T>::Evaluate(EvalContext& /*context*/)
    {
        if (timeChanged)
        {
            timeChanged = false;
            UpdateValue();
        }

        return value;
    }

    template <typename T>
    float EvalSequenceBase<T>::GetTime() const
    {
        return time;
    }

    template <typename T>
    float EvalSequenceBase<T>::GetVelocity() const
    {
        return velocity;
    }

    template <typename T>
    void EvalSequenceBase<T>::SetVelocity(float value)
    {
        velocity = value;
    }

    template <typename T>
    bool EvalSequenceBase<T>::GetLooped() const
    {
        return looped;
    }

    template <typename T>
    void EvalSequenceBase<T>::SetLooped(bool value)
    {
        looped = value;
    }

    template <typename T>
    void EvalSequenceBase<T>::SetValue(T value)
    {
        this->value = value;
    }

    template <typename T>
    void EvalSequenceBase<T>::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        time = 0.0f;
        velocity = reader.ReadFloat();
        looped = reader.ReadBool();
        timeChanged = true;
        lastTimestamp = 0;
    }

    template <typename T>
    void EvalSequenceBase<T>::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        time = o->time;
        velocity = o->velocity;
        looped = o->looped;
        timeChanged = o->timeChanged;
        value = o->value;
        lastTimestamp = o->lastTimestamp;
    }
}