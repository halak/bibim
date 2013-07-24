#pragma once
#ifndef __BIBIM_EVALUABLUNARYOPERATORS_H__
#define __BIBIM_EVALUABLUNARYOPERATORS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Evals.h>
#   include <Bibim/ComponentStreamReader.h>

    namespace Bibim
    {
        namespace EvalOperators
        {
            template <typename T, typename TOperand> struct Cast
            {
                T operator () (TOperand value) const { return static_cast<T>(value); }
            };

            template <typename T, typename TOperand> struct Negate
            {
                T operator () (TOperand value) const { return -value; }
            };

            template <typename T, typename TOperand> struct NOT
            {
                T operator () (TOperand value) const { return !value; }
            };
        }

        template <typename T, typename TOperand, template <typename U, typename UOperand> class TOperator, char a, char b, char c, char d>
        class EvalUnaryOperatorTemplate : public EvalTemplate<T>
        {
            BBComponentClass(EvalUnaryOperatorTemplate, EvalTemplate<T>, a, b, c, d);
            public:
                typedef EvalTemplate<TOperand> Eval;

            public:
                EvalUnaryOperatorTemplate() { }
                EvalUnaryOperatorTemplate(Eval* operand)
                    : operand(operand)
                {
                }

                virtual ~EvalUnaryOperatorTemplate() { }

                virtual void Start()
                {
                    if (operand)
                        operand->Start();
                }

                virtual void Stop()
                {
                    if (operand)
                        operand->Stop();
                }

                virtual void Reset()
                {
                    if (operand)
                        operand->Reset();
                }

                virtual T Evaluate(EvalContext& context)
                {
                    if (operand)
                        return op(operand->Evaluate(context));
                    else
                        return T();
                }

                Eval* GetOperand() const { return operand; }
                void SetOperand(Eval* value) { operand = value; }

            private:
                SharedPointer<Eval> operand;
                TOperator<T, TOperand> op;
        };

        typedef EvalUnaryOperatorTemplate<short, int,    EvalOperators::Cast, 'e', 'C', 's', 'i'> EvalIntToShortIntCast;
        typedef EvalUnaryOperatorTemplate<int, short,    EvalOperators::Cast, 'e', 'C', 'i', 's'> EvalShortIntToIntCast;
        typedef EvalUnaryOperatorTemplate<int, longint,  EvalOperators::Cast, 'e', 'C', 'i', 'l'> EvalLongIntToIntCast;
        typedef EvalUnaryOperatorTemplate<longint, int,  EvalOperators::Cast, 'e', 'C', 'l', 'i'> EvalIntToLongIntCast;
        typedef EvalUnaryOperatorTemplate<float, int,    EvalOperators::Cast, 'e', 'C', 'f', 'i'> EvalIntToFloatCast;
        typedef EvalUnaryOperatorTemplate<float, double, EvalOperators::Cast, 'e', 'C', 'f', 'd'> EvalDoubleToFloatCast;
        typedef EvalUnaryOperatorTemplate<double, float, EvalOperators::Cast, 'e', 'C', 'd', 'f'> EvalFloatToDoubleCast;

        typedef EvalUnaryOperatorTemplate<bool, bool,       EvalOperators::NOT,    'e', 'N', 'b', '_'> EvalBoolNegation;
        typedef EvalUnaryOperatorTemplate<int, int,         EvalOperators::Negate, 'e', 'N', 'i', '_'> EvalIntNegation;
        typedef EvalUnaryOperatorTemplate<float, float,     EvalOperators::Negate, 'e', 'N', 'f', '_'> EvalFloatNegation;
        typedef EvalUnaryOperatorTemplate<Point2, Point2,   EvalOperators::Negate, 'e', 'N', 'p', '2'> EvalPoint2Negation;
        typedef EvalUnaryOperatorTemplate<Point3, Point3,   EvalOperators::Negate, 'e', 'N', 'p', '3'> EvalPoint3Negation;
        typedef EvalUnaryOperatorTemplate<Point4, Point4,   EvalOperators::Negate, 'e', 'N', 'p', '4'> EvalPoint4Negation;
        typedef EvalUnaryOperatorTemplate<Vector2, Vector2, EvalOperators::Negate, 'e', 'N', 'v', '2'> EvalVector2Negation;
        typedef EvalUnaryOperatorTemplate<Vector3, Vector3, EvalOperators::Negate, 'e', 'N', 'v', '3'> EvalVector3Negation;
        typedef EvalUnaryOperatorTemplate<Vector4, Vector4, EvalOperators::Negate, 'e', 'N', 'v', '4'> EvalVector4Negation;

        BBDeclareEvalClass(EvalShortIntToIntCast);
        BBDeclareEvalClass(EvalLongIntToIntCast);
        BBDeclareEvalClass(EvalIntToFloatCast);
        BBDeclareEvalClass(EvalDoubleToFloatCast);
        BBDeclareEvalClass(EvalBoolNegation);
        BBDeclareEvalClass(EvalIntNegation);
        BBDeclareEvalClass(EvalFloatNegation);
        BBDeclareEvalClass(EvalPoint2Negation);
        BBDeclareEvalClass(EvalPoint3Negation);
        BBDeclareEvalClass(EvalPoint4Negation);
        BBDeclareEvalClass(EvalVector2Negation);
        BBDeclareEvalClass(EvalVector3Negation);
        BBDeclareEvalClass(EvalVector4Negation);
    }

#endif