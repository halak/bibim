#pragma once
#ifndef __BIBIM_EVALUABLEFLOATCONSTANT_H__
#define __BIBIM_EVALUABLEFLOATCONSTANT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/IFloatEvaluable.h>

    namespace Bibim
    {
        class EvaluableFloatConstant : public SharedObject, public IFloatEvaluable
        {
            typedef float ValueType;
            public:
                EvaluableFloatConstant();
                EvaluableFloatConstant(ValueType value);
                virtual ~EvaluableFloatConstant();

                virtual ValueType Evaluate();

                ValueType GetValue() const;
                void SetValue(ValueType value);

            private:
                ValueType value;
        };
    }

#endif