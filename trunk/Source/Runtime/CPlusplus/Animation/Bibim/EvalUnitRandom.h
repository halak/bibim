#pragma once
#ifndef __BIBIM_EVALUNITRANDOM_H__
#define __BIBIM_EVALUNITRANDOM_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Evals.h>

    namespace Bibim
    {
        class EvalUnitRandom : public EvalFloat
        {
            BBComponentClass(EvalUnitRandom, EvalFloat, 'e', 'U', 'R', 'f');
            public:
                enum GenerationCycle
                {
                    FullManual,
                    ResetOrManual,
                    EachTime,
                };

            public:
                EvalUnitRandom();
                virtual ~EvalUnitRandom();

                void Generate();

                virtual void Reset();
                virtual float Evaluate(EvalContext& context);

                inline int GetInitialSeed() const;
                void SetInitialSeed(int value);

                inline GenerationCycle GetCycle() const;
                inline void SetCycle(GenerationCycle value);

            private:
                float value;
                int seed;
                int initialSeed;
                GenerationCycle cycle;
        };

        BBDeclareEvalClass(EvalUnitRandom);
    }

#   include <Bibim/EvalUnitRandom.inl>

#endif