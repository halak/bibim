#pragma once
#ifndef __BIBIM_EVALUABLESPRITECONSTANT_H__
#define __BIBIM_EVALUABLESPRITECONSTANT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/ISpriteEvaluable.h>

    namespace Bibim
    {
        class EvaluableSpriteConstant : public SharedObject, public ISpriteEvaluable
        {
            typedef Sprite ValueType;
            public:
                EvaluableSpriteConstant();
                EvaluableSpriteConstant(ValueType value);
                virtual ~EvaluableSpriteConstant();

                virtual ValueType Evaluate();

                ValueType GetValue() const;
                void SetValue(ValueType value);

            private:
                ValueType value;
        };
    }

#endif