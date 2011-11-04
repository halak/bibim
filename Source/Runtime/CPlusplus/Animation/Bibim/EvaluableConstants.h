#pragma once
#ifndef __BIBIM_EVALUABLECONSTANTS_H__
#define __BIBIM_EVALUABLECONSTANTS_H__

#   include <Bibim/Evaluables.h>

    namespace Bibim
    {
        template <typename T, char a, char b, char c, char d>
        class EvaluableConstantTemplate : public EvaluableTemplate<T>
        {
            BBComponentClass(EvaluableConstantTemplate, EvaluableTemplate<T>, a, b, c, d);
            public:
                EvaluableConstantTemplate();
                EvaluableConstantTemplate(T value);
                virtual ~EvaluableConstantTemplate();
                
                virtual T Evaluate(EvaluationContext& context);

                T GetValue() const;
                void SetValue(T value);

            private:
                T value;
        };

        class EvaluableGameAssetConstant : public EvaluableGameAsset
        {
            BBComponentClass(EvaluableGameAssetConstant, EvaluableGameAsset, 'e', 'c', 'a', '_');
            public:
                EvaluableGameAssetConstant();
                EvaluableGameAssetConstant(GameAsset* value);
                virtual ~EvaluableGameAssetConstant();

                virtual GameAsset* Evaluate(EvaluationContext& context);

                inline GameAsset* GetValue() const;
                inline void SetValue(GameAsset* value);

            private:
                GameAssetPtr value;
        };

        typedef EvaluableConstantTemplate<bool,         'e', 'c', 'b', '_'> EvaluableBoolConstant;
        typedef EvaluableConstantTemplate<short,        'e', 'c', 's', '_'> EvaluableShortConstant;
        typedef EvaluableConstantTemplate<int,          'e', 'c', 'i', '_'> EvaluableIntConstant;
        typedef EvaluableConstantTemplate<int64,        'e', 'c', 'l', '_'> EvaluableLongIntConstant;
        typedef EvaluableConstantTemplate<float,        'e', 'c', 'f', '_'> EvaluableFloatConstant;
        typedef EvaluableConstantTemplate<double,       'e', 'c', 'd', '_'> EvaluableDoubleConstant;
        typedef EvaluableConstantTemplate<Point,        'e', 'c', 'p', '_'> EvaluablePointConstant;
        typedef EvaluableConstantTemplate<Rect,         'e', 'c', 'r', '_'> EvaluableRectConstant;
        typedef EvaluableConstantTemplate<RectF,        'e', 'c', 'R', 'f'> EvaluableRectFConstant;
        typedef EvaluableConstantTemplate<Vector2,      'e', 'c', 'v', '2'> EvaluableVector2Constant;
        typedef EvaluableConstantTemplate<Vector3,      'e', 'c', 'v', '3'> EvaluableVector3Constant;
        typedef EvaluableConstantTemplate<Vector4,      'e', 'c', 'v', '4'> EvaluableVector4Constant;

        typedef SharedPointer<EvaluableBoolConstant>      EvaluableBoolConstantPtr;
        typedef SharedPointer<EvaluableShortConstant>     EvaluableShortConstantPtr;
        typedef SharedPointer<EvaluableIntConstant>       EvaluableIntConstantPtr;
        typedef SharedPointer<EvaluableLongIntConstant>   EvaluableLongIntConstantPtr;
        typedef SharedPointer<EvaluableFloatConstant>     EvaluableFloatConstantPtr;
        typedef SharedPointer<EvaluableDoubleConstant>    EvaluableDoubleConstantPtr;
        typedef SharedPointer<EvaluablePointConstant>     EvaluablePointConstantPtr;
        typedef SharedPointer<EvaluableRectConstant>      EvaluableRectConstantPtr;
        typedef SharedPointer<EvaluableRectFConstant>     EvaluableRectFConstantPtr;
        typedef SharedPointer<EvaluableVector2Constant>   EvaluableVector2ConstantPtr;
        typedef SharedPointer<EvaluableVector3Constant>   EvaluableVector3ConstantPtr;
        typedef SharedPointer<EvaluableVector4Constant>   EvaluableVector4ConstantPtr;
        typedef SharedPointer<EvaluableGameAssetConstant> EvaluableGameAssetConstantPtr;
    }

#   include <Bibim/EvaluableConstants.inl>

#endif