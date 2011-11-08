#pragma once
#ifndef __BIBIM_EVALTIMEFLOW_H__
#define __BIBIM_EVALTIMEFLOW_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Evals.h>

    namespace Bibim
    {
        class EvalTimeflow : public EvalFloat
        {
            BBComponentClass(EvalTimeflow, EvalFloat, 'e', 'T', 'F', 'f');
            public:
                EvalTimeflow();
                virtual ~EvalTimeflow();

                virtual void Reset();
                virtual float Evaluate(EvalContext& context);

            private:
        };

        BBDeclareEvalClass(EvalTimeflow);
    }

#   include <Bibim/EvalTimeflow.inl>

#endif