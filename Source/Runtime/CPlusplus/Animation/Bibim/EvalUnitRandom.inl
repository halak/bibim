namespace Bibim
{
    int EvalUnitRandom::GetInitialSeed() const
    {
        return initialSeed;
    }

    EvalUnitRandom::GenerationCycle EvalUnitRandom::GetCycle() const
    {
        return cycle;
    }

    void EvalUnitRandom::SetCycle(GenerationCycle value)
    {
        cycle = value;
    }
}