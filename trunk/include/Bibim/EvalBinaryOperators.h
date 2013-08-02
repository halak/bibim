#pragma once
#ifndef __BIBIM_EVALUABLEBINARYOPERATORS_H__
#define __BIBIM_EVALUABLEBINARYOPERATORS_H__

#include <Bibim/FWD.h>
#include <Bibim/Evals.h>
#include <Bibim/Math.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    namespace EvalOperators
    {
        template <typename T, typename TLeft, typename TRight> struct Add
        {
            T operator () (TLeft left, TRight right) const { return left + right; }
        };

        template <typename T, typename TLeft, typename TRight> struct Subtract
        {
            T operator () (TLeft left, TRight right) const { return left - right; }
        };

        template <typename T, typename TLeft, typename TRight> struct Multiply
        {
            T operator () (TLeft left, TRight right) const { return left * right; }
        };

        template <typename T, typename TLeft, typename TRight> struct Divide
        {
            T operator () (TLeft left, TRight right) const { return left / right; }
        };

        template <typename T, typename TLeft, typename TRight> struct Modulus
        {
            T operator () (TLeft left, TRight right) const { return left % right; }
        };

        template <> struct Modulus<float, float, float>
        {
            float operator () (float left, float right) const { return Math::Mod(left, right); }
        };

        template <typename T, typename TLeft, typename TRight> struct AND
        {
            T operator () (TLeft left, TRight right) const { return left && right; }
        };
        
        template <typename T, typename TLeft, typename TRight> struct OR
        {
            T operator () (TLeft left, TRight right) const { return left || right; }
        };
    }

    template <typename T, typename TLeft, typename TRight, template <typename U, typename ULeft, typename URight> class TOperator, char a, char b, char c, char d>
    class EvalBinaryOperatorTemplate : public EvalTemplate<T>
    {
        BBComponentClass(EvalBinaryOperatorTemplate, EvalTemplate<T>, a, b, c, d);
        public:
            typedef EvalTemplate<TLeft>  EvalLeft;
            typedef EvalTemplate<TRight> EvalRight;

        public:
            EvalBinaryOperatorTemplate() { }
            EvalBinaryOperatorTemplate(EvalLeft* left, EvalRight* right)
                : left(left),
                  right(right)
            {
            }

            virtual ~EvalBinaryOperatorTemplate() { }

            virtual void Start()
            {
                if (left)
                    left->Start();
                if (right)
                    right->Start();
            }

            virtual void Stop()
            {
                if (left)
                    left->Stop();
                if (right)
                    right->Stop();
            }

            virtual void Reset()
            {
                if (left)
                    left->Reset();
                if (right)
                    right->Reset();
            }
           
            virtual T Evaluate(EvalContext& context)
            {
                if (left && right)
                    return op(left->Evaluate(context), right->Evaluate(context));
                else
                    return T();
            }

            EvalLeft* GetLeft() const { return left; }
            void SetLeft(EvalLeft* value) { left = value; }

            EvalRight* GetRight() const { return right; }
            void SetRight(EvalRight* value) { right = value; }

        protected:

        private:
            SharedPointer<EvalLeft> left;
            SharedPointer<EvalRight> right;
            TOperator<T, TLeft, TRight> op;
    };

    typedef EvalBinaryOperatorTemplate<bool, bool, bool, EvalOperators::AND, 'e', 'A', 'N', 'b'> EvalBoolAND;
    typedef EvalBinaryOperatorTemplate<bool, bool, bool, EvalOperators::OR,  'e', 'O', 'R', 'b'> EvalBoolOR;

    typedef EvalBinaryOperatorTemplate<int, int, int, EvalOperators::Add,      'e', 'A', 'i', '_'> EvalIntAddition;
    typedef EvalBinaryOperatorTemplate<int, int, int, EvalOperators::Subtract, 'e', 'S', 'i', '_'> EvalIntSubtraction;
    typedef EvalBinaryOperatorTemplate<int, int, int, EvalOperators::Multiply, 'e', 'X', 'i', '_'> EvalIntMultiplication;
    typedef EvalBinaryOperatorTemplate<int, int, int, EvalOperators::Divide,   'e', 'D', 'i', '_'> EvalIntDivision;
    typedef EvalBinaryOperatorTemplate<int, int, int, EvalOperators::Modulus,  'e', 'M', 'i', '_'> EvalIntModulus;

    typedef EvalBinaryOperatorTemplate<float, float, float, EvalOperators::Add,      'e', 'A', 'f', '_'> EvalFloatAddition;
    typedef EvalBinaryOperatorTemplate<float, float, float, EvalOperators::Subtract, 'e', 'S', 'f', '_'> EvalFloatSubtraction;
    typedef EvalBinaryOperatorTemplate<float, float, float, EvalOperators::Multiply, 'e', 'X', 'f', '_'> EvalFloatMultiplication;
    typedef EvalBinaryOperatorTemplate<float, float, float, EvalOperators::Divide,   'e', 'D', 'f', '_'> EvalFloatDivision;
    typedef EvalBinaryOperatorTemplate<float, float, float, EvalOperators::Modulus,  'e', 'M', 'f', '_'> EvalFloatModulus;

    typedef EvalBinaryOperatorTemplate<Point2, Point2, Point2, EvalOperators::Add,      'e', 'A', 'p', '2'> EvalPoint2Addition;
    typedef EvalBinaryOperatorTemplate<Point2, Point2, Point2, EvalOperators::Subtract, 'e', 'S', 'p', '2'> EvalPoint2Subtraction;
    typedef EvalBinaryOperatorTemplate<Point2, Point2, int,    EvalOperators::Multiply, 'e', 'X', 'p', '2'> EvalPoint2Multiplication;
    typedef EvalBinaryOperatorTemplate<Point2, Point2, int,    EvalOperators::Divide,   'e', 'D', 'p', '2'> EvalPoint2Division;

    typedef EvalBinaryOperatorTemplate<Point3, Point3, Point3, EvalOperators::Add,      'e', 'A', 'p', '3'> EvalPoint3Addition;
    typedef EvalBinaryOperatorTemplate<Point3, Point3, Point3, EvalOperators::Subtract, 'e', 'S', 'p', '3'> EvalPoint3Subtraction;
    typedef EvalBinaryOperatorTemplate<Point3, Point3, int,    EvalOperators::Multiply, 'e', 'X', 'p', '3'> EvalPoint3Multiplication;
    typedef EvalBinaryOperatorTemplate<Point3, Point3, int,    EvalOperators::Divide,   'e', 'D', 'p', '3'> EvalPoint3Division;

    typedef EvalBinaryOperatorTemplate<Point4, Point4, Point4, EvalOperators::Add,      'e', 'A', 'p', '4'> EvalPoint4Addition;
    typedef EvalBinaryOperatorTemplate<Point4, Point4, Point4, EvalOperators::Subtract, 'e', 'S', 'p', '4'> EvalPoint4Subtraction;
    typedef EvalBinaryOperatorTemplate<Point4, Point4, int,    EvalOperators::Multiply, 'e', 'X', 'p', '4'> EvalPoint4Multiplication;
    typedef EvalBinaryOperatorTemplate<Point4, Point4, int,    EvalOperators::Divide,   'e', 'D', 'p', '4'> EvalPoint4Division;

    typedef EvalBinaryOperatorTemplate<Vector2, Vector2, Vector2, EvalOperators::Add,      'e', 'A', 'v', '2'> EvalVector2Addition;
    typedef EvalBinaryOperatorTemplate<Vector2, Vector2, Vector2, EvalOperators::Subtract, 'e', 'S', 'v', '2'> EvalVector2Subtraction;
    typedef EvalBinaryOperatorTemplate<Vector2, Vector2, float,   EvalOperators::Multiply, 'e', 'X', 'v', '2'> EvalVector2Multiplication;
    typedef EvalBinaryOperatorTemplate<Vector2, Vector2, float,   EvalOperators::Divide,   'e', 'D', 'v', '2'> EvalVector2Division;

    typedef EvalBinaryOperatorTemplate<Vector3, Vector3, Vector3, EvalOperators::Add,      'e', 'A', 'v', '3'> EvalVector3Addition;
    typedef EvalBinaryOperatorTemplate<Vector3, Vector3, Vector3, EvalOperators::Subtract, 'e', 'S', 'v', '3'> EvalVector3Subtraction;
    typedef EvalBinaryOperatorTemplate<Vector3, Vector3, float,   EvalOperators::Multiply, 'e', 'X', 'v', '3'> EvalVector3Multiplication;
    typedef EvalBinaryOperatorTemplate<Vector3, Vector3, float,   EvalOperators::Divide,   'e', 'D', 'v', '3'> EvalVector3Division;

    typedef EvalBinaryOperatorTemplate<Vector4, Vector4, Vector4, EvalOperators::Add,      'e', 'A', 'v', '4'> EvalVector4Addition;
    typedef EvalBinaryOperatorTemplate<Vector4, Vector4, Vector4, EvalOperators::Subtract, 'e', 'S', 'v', '4'> EvalVector4Subtraction;
    typedef EvalBinaryOperatorTemplate<Vector4, Vector4, float,   EvalOperators::Multiply, 'e', 'X', 'v', '4'> EvalVector4Multiplication;
    typedef EvalBinaryOperatorTemplate<Vector4, Vector4, float,   EvalOperators::Divide,   'e', 'D', 'v', '4'> EvalVector4Division;

    BBDeclareEvalClass(EvalBoolAND);
    BBDeclareEvalClass(EvalBoolOR);
    BBDeclareEvalClass(EvalIntAddition);
    BBDeclareEvalClass(EvalIntSubtraction);
    BBDeclareEvalClass(EvalIntMultiplication);
    BBDeclareEvalClass(EvalIntDivision);
    BBDeclareEvalClass(EvalIntModulus);
    BBDeclareEvalClass(EvalFloatAddition);
    BBDeclareEvalClass(EvalFloatSubtraction);
    BBDeclareEvalClass(EvalFloatMultiplication);
    BBDeclareEvalClass(EvalFloatDivision);
    BBDeclareEvalClass(EvalFloatModulus);
    BBDeclareEvalClass(EvalPoint2Addition);
    BBDeclareEvalClass(EvalPoint2Subtraction);
    BBDeclareEvalClass(EvalPoint2Multiplication);
    BBDeclareEvalClass(EvalPoint2Division);
    BBDeclareEvalClass(EvalPoint3Addition);
    BBDeclareEvalClass(EvalPoint3Subtraction);
    BBDeclareEvalClass(EvalPoint3Multiplication);
    BBDeclareEvalClass(EvalPoint3Division);
    BBDeclareEvalClass(EvalPoint4Addition);
    BBDeclareEvalClass(EvalPoint4Subtraction);
    BBDeclareEvalClass(EvalPoint4Multiplication);
    BBDeclareEvalClass(EvalPoint4Division);
    BBDeclareEvalClass(EvalVector2Addition);
    BBDeclareEvalClass(EvalVector2Subtraction);
    BBDeclareEvalClass(EvalVector2Multiplication);
    BBDeclareEvalClass(EvalVector2Division);
    BBDeclareEvalClass(EvalVector3Addition);
    BBDeclareEvalClass(EvalVector3Subtraction);
    BBDeclareEvalClass(EvalVector3Multiplication);
    BBDeclareEvalClass(EvalVector3Division);
    BBDeclareEvalClass(EvalVector4Addition);
    BBDeclareEvalClass(EvalVector4Subtraction);
    BBDeclareEvalClass(EvalVector4Multiplication);
    BBDeclareEvalClass(EvalVector4Division);

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename T, typename TLeft, typename TRight, template <typename U, typename ULeft, typename URight> class TOperator, char a, char b, char c, char d>
    EvalBinaryOperatorTemplate<T, TLeft, TRight, TOperator, a, b, c, d>* EvalBinaryOperatorTemplate<T, TLeft, TRight, TOperator, a, b, c, d>::Clone() const
    {
        CloningContext context;
        return Clone(context);
    }

    template <typename T, typename TLeft, typename TRight, template <typename U, typename ULeft, typename URight> class TOperator, char a, char b, char c, char d>
    EvalBinaryOperatorTemplate<T, TLeft, TRight, TOperator, a, b, c, d>* EvalBinaryOperatorTemplate<T, TLeft, TRight, TOperator, a, b, c, d>::Clone(CloningContext& context) const
    {
        This* clone = new This();
        context.Store(this, clone);
        clone->OnCopy(this, context);
        return clone;
    }

    template <typename T, typename TLeft, typename TRight, template <typename U, typename ULeft, typename URight> class TOperator, char a, char b, char c, char d>
    void EvalBinaryOperatorTemplate<T, TLeft, TRight, TOperator, a, b, c, d>::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        left = static_cast<EvalLeft*>(reader.ReadComponent());
        right = static_cast<EvalRight*>(reader.ReadComponent());
    }

    template <typename T, typename TLeft, typename TRight, template <typename U, typename ULeft, typename URight> class TOperator, char a, char b, char c, char d>
    void EvalBinaryOperatorTemplate<T, TLeft, TRight, TOperator, a, b, c, d>::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        left = context.Clone(o->left);
        right = context.Clone(o->right);
    }
}

#endif