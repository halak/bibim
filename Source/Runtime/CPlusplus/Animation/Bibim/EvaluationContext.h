#pragma once
#ifndef __BIBIM_EVALUATIONCONTEXT_H__
#define __BIBIM_EVALUATIONCONTEXT_H__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class EvaluationContext
        {
            public:
                EvaluationContext();
                ~EvaluationContext();

                template <typename T>
                T GetValue(const String& name);

            private:
        };
    }

#   include <Bibim/EvaluationContext.inl>

#endif