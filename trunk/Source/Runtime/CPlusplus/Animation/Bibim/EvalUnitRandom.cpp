#include <Bibim/PCH.h>
#include <Bibim/EvalUnitRandom.h>
#include <Bibim/Clock.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Math.h>

namespace Bibim
{
    BBImplementsComponent(EvalUnitRandom);

    EvalUnitRandom::EvalUnitRandom()
        : value(0.0f),
          seed(0),
          initialSeed(0),
          cycle(EachTime)
    {
    }

    EvalUnitRandom::~EvalUnitRandom()
    {
    }

    void EvalUnitRandom::Generate()
    {
        const int generatedValue = seed % 1001;
        value = static_cast<float>(generatedValue) * 0.001f;
        seed = 49327 * (seed & 0xABCDABCD) + (seed >> 16);

        if (seed == 0)
        {
            if (initialSeed != 0)
                seed = initialSeed;
            else
                seed = static_cast<int>(Clock::GetCurrentMilliSeconds());
        }
    }

    void EvalUnitRandom::Reset()
    {
        if (cycle == ResetOrManual)
            Generate();
    }

    float EvalUnitRandom::Evaluate(EvalContext& /*context*/)
    {
        if (cycle == EachTime)
            Generate();

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

            Generate();
        }
    }

    void EvalUnitRandom::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        initialSeed = reader.ReadInt();
        cycle = static_cast<GenerationCycle>(reader.ReadByte());
        seed = initialSeed;
        Generate();
    }

    void EvalUnitRandom::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        value = o->value;
        seed = o->seed;
        initialSeed = o->initialSeed;
        cycle = o->cycle;
    }
}