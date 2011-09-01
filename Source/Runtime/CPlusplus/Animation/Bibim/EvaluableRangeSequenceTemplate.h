#pragma once
#ifndef __BIBIM_EVALUABLERANGESEQUENCETEMPLATE_H__
#define __BIBIM_EVALUABLERANGESEQUENCETEMPLATE_H__
/**
#   include <Bibim/FWD.h>
#   include <Bibim/EvaluableSequenceTemplate.h>
#   include <random>

    namespace Bibim
    {
        template <typename T> class EvaluableRangeSequenceTemplate : public EvaluableSequenceTemplate<T>
        {
            public:
                typedef typename ValueType::ElementType ElementType;

            public:
                EvaluableRangeSequenceTemplate();
                EvaluableRangeSequenceTemplate(ulong seed);
                ~EvaluableRangeSequenceTemplate();

                // ""overloading""
                ElementType Evaluate();

                void SetSeed(ulong seed);

            private:
                // ""overloading""
                void UpdateValue();

            private:
                std::tr1::mt19937 randomEngine;
                std::tr1::uniform_real<float> normalize;
                ElementType range[2];
                ElementType value;
        };
    }

#   include <Bibim/EvaluableRangeSequenceTemplate.inl>
**/
#endif