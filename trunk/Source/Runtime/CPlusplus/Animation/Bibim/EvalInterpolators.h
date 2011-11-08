#pragma once
#ifndef __BIBIM_EvalInterpolatorS_H__
#define __BIBIM_EvalInterpolatorS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Evals.h>
#   include <Bibim/Math.h>

    namespace Bibim
    {
        namespace EvalOperators
        {
            template <typename T> struct Lerp
            {
                T operator () (T a, T b, float t) const { return Math::Lerp(a, b, t); }
            };
        }

        template <typename T, template <typename T> class TOperator, char a, char b, char c, char d>
        class EvalInterpolatorTemplate : public EvalTemplate<T>
        {
            BBComponentClass(EvalInterpolatorTemplate, EvalTemplate<T>, a, b, c, d);
            public:
                typedef EvalTemplate<T> EvalValue;

            public:
                EvalInterpolatorTemplate() { }
                EvalInterpolatorTemplate(EvalValue* value1, EvalValue* value2, EvalFloat* weight)
                    : value1(value1),
                      value2(value2), 
                      weight(weight)
                {
                }

                virtual ~EvalInterpolatorTemplate() { }

                virtual void Reset()
                {
                    if (value1)
                        value1->Reset();
                    if (value2)
                        value2->Reset():
                    if (weight)
                        weight->Reset();
                }

                virtual T Evaluate(EvalContext& context)
                {
                    if (value1 && value2 && weight)
                        return op(value1->Evaluate(context), value2->Evaluate(context), weight->Evaluate(context));
                    else
                        return T();
                }

                EvalValue* GetValue1() const { return value1; }
                void SetValue1(EvalValue* value) { value1 = value; }

                EvalValue* GetValue2() const { return value2; }
                void SetValue2(EvalValue* value) { value2 = value; }

                EvalFloat* GetWeight() const { return weight ; }
                void SetWeigt(EvalFloat* value) { weight = value; }

            private:
                SharedPointer<EvalValue> value1;
                SharedPointer<EvalValue> value2;
                EvalFloatPtr weight;
                TOperator<T> op;
        };

        typedef EvalInterpolatorTemplate<short,   EvalOperators::Lerp, 'e', 'I', 's', '_'> EvalShortIntInterpolator;
        typedef EvalInterpolatorTemplate<int,     EvalOperators::Lerp, 'e', 'I', 'i', '_'> EvalIntInterpolator;
        typedef EvalInterpolatorTemplate<longint, EvalOperators::Lerp, 'e', 'I', 'l', '_'> EvalLongIntInterpolator;
        typedef EvalInterpolatorTemplate<float,   EvalOperators::Lerp, 'e', 'I', 'f', '_'> EvalFloatInterpolator;
        typedef EvalInterpolatorTemplate<double,  EvalOperators::Lerp, 'e', 'I', 'd', '_'> EvalDoubleInterpolator;
        typedef EvalInterpolatorTemplate<Color,   EvalOperators::Lerp, 'e', 'I', 'c', '_'> EvalColorInterpolator;
        typedef EvalInterpolatorTemplate<Point2,  EvalOperators::Lerp, 'e', 'I', 'p', '2'> EvalPoint2Interpolator;
        typedef EvalInterpolatorTemplate<Point3,  EvalOperators::Lerp, 'e', 'I', 'p', '3'> EvalPoint3Interpolator;
        typedef EvalInterpolatorTemplate<Point4,  EvalOperators::Lerp, 'e', 'I', 'p', '4'> EvalPoint4Interpolator;
        typedef EvalInterpolatorTemplate<Vector2, EvalOperators::Lerp, 'e', 'I', 'v', '2'> EvalVector2Interpolator;
        typedef EvalInterpolatorTemplate<Vector3, EvalOperators::Lerp, 'e', 'I', 'v', '3'> EvalVector3Interpolator;
        typedef EvalInterpolatorTemplate<Vector4, EvalOperators::Lerp, 'e', 'I', 'v', '4'> EvalVector4Interpolator;

        BBDeclareEvalClass(EvalShortIntInterpolator);
        BBDeclareEvalClass(EvalIntInterpolator);
        BBDeclareEvalClass(EvalLongIntInterpolator);
        BBDeclareEvalClass(EvalFloatInterpolator);
        BBDeclareEvalClass(EvalDoubleInterpolator);
        BBDeclareEvalClass(EvalColorInterpolator);
        BBDeclareEvalClass(EvalPoint2Interpolator);
        BBDeclareEvalClass(EvalPoint3Interpolator);
        BBDeclareEvalClass(EvalPoint4Interpolator);
        BBDeclareEvalClass(EvalVector2Interpolator);
        BBDeclareEvalClass(EvalVector3Interpolator);
        BBDeclareEvalClass(EvalVector4Interpolator);
    }

#   include <Bibim/EvalInterpolators.inl>

#endif