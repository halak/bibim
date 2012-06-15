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
                EvalUnitRandom();
                virtual ~EvalUnitRandom();

                virtual void Start() { }
                virtual void Stop()  { }
                virtual void Reset() { }
                virtual float Evaluate(EvalContext& context);

                inline int GetInitialSeed() const;
                void SetInitialSeed(int value);

            private:
                int seed;
                int initialSeed;
        };

        BBDeclareEvalClass(EvalUnitRandom);
    }

#   include <Bibim/EvalUnitRandom.inl>

#endif