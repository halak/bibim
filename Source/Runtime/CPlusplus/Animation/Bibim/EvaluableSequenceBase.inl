#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    template <typename T>
    EvaluableSequenceBase<T>::EvaluableSequenceBase()
        : time(0.0f),
          velocity(1.0f),
          looped(false),
          timeChanged(true),
          value(),
          lastTimestamp(0)
    {
    }
    
    template <typename T>
    EvaluableSequenceBase<T>::~EvaluableSequenceBase()
    {
    }

    template <typename T>
    void EvaluableSequenceBase<T>::Update(float dt, uint timestamp)
    {
        if (lastTimestamp == timestamp)
            return;
        else
            lastTimestamp = timestamp;

        time += dt;
        timeChanged = true;
    }

    template <typename T>
    T EvaluableSequenceBase<T>::Evaluate(EvaluationContext& /*context*/)
    {
        if (timeChanged)
        {
            timeChanged = false;
            UpdateValue();
        }

        return value;
    }

    template <typename T>
    float EvaluableSequenceBase<T>::GetTime() const
    {
        return time;
    }

    template <typename T>
    float EvaluableSequenceBase<T>::GetVelocity() const
    {
        return velocity;
    }

    template <typename T>
    void EvaluableSequenceBase<T>::SetVelocity(float value)
    {
        velocity = value;
    }

    template <typename T>
    bool EvaluableSequenceBase<T>::GetLooped() const
    {
        return looped;
    }

    template <typename T>
    void EvaluableSequenceBase<T>::SetLooped(bool value)
    {
        looped = value;
    }

    template <typename T>
    void EvaluableSequenceBase<T>::SetValue(T value)
    {
        this->value = value;
    }

    template <typename T>
    void EvaluableSequenceBase<T>::OnRead(ComponentStreamReader& reader)
    {
        Base::onRead(reader);
        time = 0.0f;
        velocity = reader.ReadFloat();
        looped = reader.ReadBool();
        timeChanged = true;
        lastTimestamp = 0;
    }

    template <typename T>
    void EvaluableSequenceBase<T>::OnCopy(const GameComponent* original, CloningContext& context)
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