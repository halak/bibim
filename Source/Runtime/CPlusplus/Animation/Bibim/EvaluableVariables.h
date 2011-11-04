#pragma once
#ifndef __BIBIM_EVALUABLEVARIABLES_H__
#define __BIBIM_EVALUABLEVARIABLES_H__

#   include <Bibim/Evaluables.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
        template <typename T, char a, char b, char c, char d>
        class EvaluableVariableTemplate : public EvaluableTemplate<T>
        {
            BBComponentClass(EvaluableVariableTemplate, EvaluableTemplate<T>, a, b, c, d);
            public:
                EvaluableVariableTemplate();
                EvaluableVariableTemplate(const String& name);
                virtual ~EvaluableVariableTemplate();
                
                virtual T Evaluate(EvaluationContext& context);

                const String& GetName() const;
                void SetName(const String& value);

            private:
                T name;
        };

        typedef EvaluableVariableTemplate<bool,         'e', 'v', 'b', '_'> EvaluableBoolVariable;
        typedef EvaluableVariableTemplate<short,        'e', 'v', 's', '_'> EvaluableShortIntVariable;
        typedef EvaluableVariableTemplate<int,          'e', 'v', 'i', '_'> EvaluableIntVariable;
        typedef EvaluableVariableTemplate<int64,        'e', 'v', 'l', '_'> EvaluableLongIntVariable;
        typedef EvaluableVariableTemplate<float,        'e', 'v', 'f', '_'> EvaluableFloatVariable;
        typedef EvaluableVariableTemplate<double,       'e', 'v', 'd', '_'> EvaluableDoubleVariable;
        typedef EvaluableVariableTemplate<Point,        'e', 'v', 'p', '_'> EvaluablePointVariable;
        typedef EvaluableVariableTemplate<Rect,         'e', 'v', 'r', '_'> EvaluableRectVariable;
        typedef EvaluableVariableTemplate<RectF,        'e', 'v', 'R', 'f'> EvaluableRectFVariable;
        typedef EvaluableVariableTemplate<Vector2,      'e', 'v', 'v', '2'> EvaluableVector2Variable;
        typedef EvaluableVariableTemplate<Vector3,      'e', 'v', 'v', '3'> EvaluableVector3Variable;
        typedef EvaluableVariableTemplate<Vector4,      'e', 'v', 'v', '4'> EvaluableVector4Variable;
        typedef EvaluableVariableTemplate<GameAsset*,   'e', 'v', 'a', '_'> EvaluableGameAssetVariable;

        typedef SharedPointer<EvaluableBoolVariable>      EvaluableBoolVariablePtr;
        typedef SharedPointer<EvaluableShortIntVariable>  EvaluableShortIntVariablePtr;
        typedef SharedPointer<EvaluableIntVariable>       EvaluableIntVariablePtr;
        typedef SharedPointer<EvaluableLongIntVariable>   EvaluableLongIntVariablePtr;
        typedef SharedPointer<EvaluableFloatVariable>     EvaluableFloatVariablePtr;
        typedef SharedPointer<EvaluableDoubleVariable>    EvaluableDoubleVariablePtr;
        typedef SharedPointer<EvaluablePointVariable>     EvaluablePointVariablePtr;
        typedef SharedPointer<EvaluableRectVariable>      EvaluableRectVariablePtr;
        typedef SharedPointer<EvaluableRectFVariable>     EvaluableRectFVariablePtr;
        typedef SharedPointer<EvaluableVector2Variable>   EvaluableVector2VariablePtr;
        typedef SharedPointer<EvaluableVector3Variable>   EvaluableVector3VariablePtr;
        typedef SharedPointer<EvaluableVector4Variable>   EvaluableVector4VariablePtr;
        typedef SharedPointer<EvaluableGameAssetVariable> EvaluableGameAssetVariablePtr;
    }

#   include <Bibim/EvaluableConstants.inl>

#endif