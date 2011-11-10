#pragma once
#ifndef __BIBIM_EVALUABLECONSTANTS_H__
#define __BIBIM_EVALUABLECONSTANTS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Evals.h>

    namespace Bibim
    {
        template <typename T, char a, char b, char c, char d>
        class EvalConstantTemplate : public EvalTemplate<T>
        {
            BBComponentClass(EvalConstantTemplate, EvalTemplate<T>, a, b, c, d);
            public:
                EvalConstantTemplate() { }
                EvalConstantTemplate(T value)
                    : value(value) 
                {
                }
                virtual ~EvalConstantTemplate() { }
               
                virtual void Start() { }
                virtual void Stop()  { }
                virtual void Reset() { }
                virtual T Evaluate(EvalContext& /*context*/)
                {
                    return value;
                }

                T GetValue() const { return value; }
                void SetValue(T value) { this->value = value; }

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

                virtual void Start() { }
                virtual void Stop()  { }
                virtual void Reset() { }
                virtual GameAsset* Evaluate(EvalContext& context);

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

        BBDeclareEvalClass(EvalBoolConstant);
        BBDeclareEvalClass(EvalShortIntConstant);
        BBDeclareEvalClass(EvalIntConstant);
        BBDeclareEvalClass(EvalLongIntConstant);
        BBDeclareEvalClass(EvalFloatConstant);
        BBDeclareEvalClass(EvalDoubleConstant);
        BBDeclareEvalClass(EvalColorConstant);
        BBDeclareEvalClass(EvalPoint2Constant);
        BBDeclareEvalClass(EvalPoint3Constant);
        BBDeclareEvalClass(EvalPoint4Constant);
        BBDeclareEvalClass(EvalRectConstant);
        BBDeclareEvalClass(EvalRectFConstant);
        BBDeclareEvalClass(EvalVector2Constant);
        BBDeclareEvalClass(EvalVector3Constant);
        BBDeclareEvalClass(EvalVector4Constant);
        BBDeclareEvalClass(EvalGameAssetConstant);
    }

#   include <Bibim/EvalConstants.inl>

#endif