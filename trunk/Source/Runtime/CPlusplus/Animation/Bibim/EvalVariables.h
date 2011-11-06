#pragma once
#ifndef __BIBIM_EVALUABLEVARIABLES_H__
#define __BIBIM_EVALUABLEVARIABLES_H__

#   include <Bibim/Evals.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
        template <typename T, char a, char b, char c, char d>
        class EvalVariableTemplate : public EvalTemplate<T>
        {
            BBComponentClass(EvalVariableTemplate, EvalTemplate<T>, a, b, c, d);
            public:
                EvalVariableTemplate();
                EvalVariableTemplate(const String& name);
                virtual ~EvalVariableTemplate();
                
                virtual T Evaluate(EvalContext& context);

                const String& GetName() const;
                void SetName(const String& value);

            private:
                String name;
        };

        typedef EvalVariableTemplate<bool,         'e', 'v', 'b', '_'> EvalBoolVariable;
        typedef EvalVariableTemplate<short,        'e', 'v', 's', '_'> EvalShortIntVariable;
        typedef EvalVariableTemplate<int,          'e', 'v', 'i', '_'> EvalIntVariable;
        typedef EvalVariableTemplate<longint,      'e', 'v', 'l', '_'> EvalLongIntVariable;
        typedef EvalVariableTemplate<float,        'e', 'v', 'f', '_'> EvalFloatVariable;
        typedef EvalVariableTemplate<double,       'e', 'v', 'd', '_'> EvalDoubleVariable;
        typedef EvalVariableTemplate<Color,        'e', 'v', 'c', '_'> EvalColorVariable;
        typedef EvalVariableTemplate<Point2,       'e', 'v', 'p', '2'> EvalPoint2Variable;
        typedef EvalVariableTemplate<Point3,       'e', 'v', 'p', '3'> EvalPoint3Variable;
        typedef EvalVariableTemplate<Point4,       'e', 'v', 'p', '4'> EvalPoint4Variable;
        typedef EvalVariableTemplate<Rect,         'e', 'v', 'r', '_'> EvalRectVariable;
        typedef EvalVariableTemplate<RectF,        'e', 'v', 'R', 'f'> EvalRectFVariable;
        typedef EvalVariableTemplate<Vector2,      'e', 'v', 'v', '2'> EvalVector2Variable;
        typedef EvalVariableTemplate<Vector3,      'e', 'v', 'v', '3'> EvalVector3Variable;
        typedef EvalVariableTemplate<Vector4,      'e', 'v', 'v', '4'> EvalVector4Variable;
        typedef EvalVariableTemplate<GameAsset*,   'e', 'v', 'a', '_'> EvalGameAssetVariable;

        typedef SharedPointer<EvalBoolVariable>      EvalBoolVariablePtr;
        typedef SharedPointer<EvalShortIntVariable>  EvalShortIntVariablePtr;
        typedef SharedPointer<EvalIntVariable>       EvalIntVariablePtr;
        typedef SharedPointer<EvalLongIntVariable>   EvalLongIntVariablePtr;
        typedef SharedPointer<EvalFloatVariable>     EvalFloatVariablePtr;
        typedef SharedPointer<EvalDoubleVariable>    EvalDoubleVariablePtr;
        typedef SharedPointer<EvalColorVariable>     EvalColorVariablePtr;
        typedef SharedPointer<EvalPoint2Variable>    EvalPoint2VariablePtr;
        typedef SharedPointer<EvalPoint3Variable>    EvalPoint3VariablePtr;
        typedef SharedPointer<EvalPoint4Variable>    EvalPoint4VariablePtr;
        typedef SharedPointer<EvalRectVariable>      EvalRectVariablePtr;
        typedef SharedPointer<EvalRectFVariable>     EvalRectFVariablePtr;
        typedef SharedPointer<EvalVector2Variable>   EvalVector2VariablePtr;
        typedef SharedPointer<EvalVector3Variable>   EvalVector3VariablePtr;
        typedef SharedPointer<EvalVector4Variable>   EvalVector4VariablePtr;
        typedef SharedPointer<EvalGameAssetVariable> EvalGameAssetVariablePtr;
    }

#   include <Bibim/EvalVariables.inl>

#endif