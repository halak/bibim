#include <Bibim/PCH.h>
#include <Bibim/EvalUnitRandom.h>
#include <Bibim/Clock.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Math.h>

namespace Bibim
{
    BBImplementsComponent(EvalUnitRandom);

    EvalUnitRandom::EvalUnitRandom()
        : seed(0),
          initialSeed(0)
    {
    }

    EvalUnitRandom::~EvalUnitRandom()
    {
    }

    float EvalUnitRandom::Evaluate(EvalContext& /*context*/)
    {
        const int generatedValue = seed % 1001;
        const float value = static_cast<float>(generatedValue) * 0.001f;
        seed = 49327 * (seed & 0xABCDABCD) + (seed >> 16);

        if (seed == 0)
        {
            if (initialSeed != 0)
                seed = initialSeed;
            else
                seed = static_cast<int>(Clock::GetCurrentMilliSeconds());
        }

        return value;
    }

    void EvalUnitRandom::SetInitialSeed(int value)
    {
        value = Math::Max(value, 0);
        if (initialSeed != value)
        {
            initialSeed = value;

            if (initialSeed != 0)
                seed = initialSeed;
            else
                seed = static_cast<int>(Clock::GetCurrentMilliSeconds());
        }
    }

    void EvalUnitRandom::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        initialSeed = reader.ReadInt();
        seed = initialSeed;
    }

    void EvalUnitRandom::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        seed = o->seed;
        initialSeed = o->initialSeed;
    }
}