#pragma once
#ifndef __BIBIM_EVALUABLECONSTANTS_H__
#define __BIBIM_EVALUABLECONSTANTS_H__

#   include <Bibim/Evals.h>

    namespace Bibim
    {
        template <typename T, char a, char b, char c, char d>
        class EvalConstantTemplate : public EvalTemplate<T>
        {
            BBComponentClass(EvalConstantTemplate, EvalTemplate<T>, a, b, c, d);
            public:
                EvalConstantTemplate();
                EvalConstantTemplate(T value);
                virtual ~EvalConstantTemplate();
                
                virtual T Evaluate(EvaluationContext& context);

                T GetValue() const;
                void SetValue(T value);

            private:
                T value;
        };

        class EvalGameAssetConstant : public EvalGameAsset
        {
            BBComponentClass(EvalGameAssetConstant, EvalGameAsset, 'e', 'c', 'a', '_');
            public:
                EvalGameAssetConstant();
                EvalGameAssetConstant(GameAsset* value);
                virtual ~EvalGameAssetConstant();

                virtual GameAsset* Evaluate(EvaluationContext& context);

                inline GameAsset* GetValue() const;
                inline void SetValue(GameAsset* value);

            private:
                GameAssetPtr value;
        };

        typedef EvalConstantTemplate<bool,         'e', 'c', 'b', '_'> EvalBoolConstant;
        typedef EvalConstantTemplate<short,        'e', 'c', 's', '_'> EvalShortIntConstant;
        typedef EvalConstantTemplate<int,          'e', 'c', 'i', '_'> EvalIntConstant;
        typedef EvalConstantTemplate<longint,      'e', 'c', 'l', '_'> EvalLongIntConstant;
        typedef EvalConstantTemplate<float,        'e', 'c', 'f', '_'> EvalFloatConstant;
        typedef EvalConstantTemplate<double,       'e', 'c', 'd', '_'> EvalDoubleConstant;
        typedef EvalConstantTemplate<Color,        'e', 'c', 'c', '_'> EvalColorConstant;
        typedef EvalConstantTemplate<Point2,       'e', 'c', 'p', '2'> EvalPoint2Constant;
        typedef EvalConstantTemplate<Point3,       'e', 'c', 'p', '3'> EvalPoint3Constant;
        typedef EvalConstantTemplate<Point4,       'e', 'c', 'p', '4'> EvalPoint4Constant;
        typedef EvalConstantTemplate<Rect,         'e', 'c', 'r', '_'> EvalRectConstant;
        typedef EvalConstantTemplate<RectF,        'e', 'c', 'R', 'f'> EvalRectFConstant;
        typedef EvalConstantTemplate<Vector2,      'e', 'c', 'v', '2'> EvalVector2Constant;
        typedef EvalConstantTemplate<Vector3,      'e', 'c', 'v', '3'> EvalVector3Constant;
        typedef EvalConstantTemplate<Vector4,      'e', 'c', 'v', '4'> EvalVector4Constant;

        typedef SharedPointer<EvalBoolConstant>      EvalBoolConstantPtr;
        typedef SharedPointer<EvalShortIntConstant>  EvalShortIntConstantPtr;
        typedef SharedPointer<EvalIntConstant>       EvalIntConstantPtr;
        typedef SharedPointer<EvalLongIntConstant>   EvalLongIntConstantPtr;
        typedef SharedPointer<EvalFloatConstant>     EvalFloatConstantPtr;
        typedef SharedPointer<EvalDoubleConstant>    EvalDoubleConstantPtr;
        typedef SharedPointer<EvalColorConstant>     EvalColorConstantPtr;
        typedef SharedPointer<EvalPoint2Constant>    EvalPoint2ConstantPtr;
        typedef SharedPointer<EvalPoint3Constant>    EvalPoint3ConstantPtr;
        typedef SharedPointer<EvalPoint4Constant>    EvalPoint4ConstantPtr;
        typedef SharedPointer<EvalRectConstant>      EvalRectConstantPtr;
        typedef SharedPointer<EvalRectFConstant>     EvalRectFConstantPtr;
        typedef SharedPointer<EvalVector2Constant>   EvalVector2ConstantPtr;
        typedef SharedPointer<EvalVector3Constant>   EvalVector3ConstantPtr;
        typedef SharedPointer<EvalVector4Constant>   EvalVector4ConstantPtr;
        typedef SharedPointer<EvalGameAssetConstant> EvalGameAssetConstantPtr;
    }

#   include <Bibim/EvalConstants.inl>

#endif