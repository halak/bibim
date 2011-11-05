#pragma once
#ifndef __BIBIM_EVALUABLES_H__
#define __BIBIM_EVALUABLES_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameComponent.h>
#   include <Bibim/Color.h>
#   include <Bibim/Point2.h>
#   include <Bibim/Point3.h>
#   include <Bibim/Point4.h>
#   include <Bibim/Rect.h>
#   include <Bibim/Vector2.h>
#   include <Bibim/Vector3.h>
#   include <Bibim/Vector4.h>

    namespace Bibim
    {
        template <typename T> class EvalTemplate : public GameComponent
        {
            BBAbstractComponentClass(EvalTemplate, GameComponent);
            public:
                virtual ~EvalTemplate() { }

                virtual T Evaluate(EvaluationContext& context) = 0;
        };

        typedef EvalTemplate<bool>       EvalBool;
        typedef EvalTemplate<short>      EvalShortInt;
        typedef EvalTemplate<int>        EvalInt;
        typedef EvalTemplate<longint>    EvalLongInt;
        typedef EvalTemplate<float>      EvalFloat;
        typedef EvalTemplate<double>     EvalDouble;
        typedef EvalTemplate<Color>      EvalColor;
        typedef EvalTemplate<Point2>     EvalPoint2;
        typedef EvalTemplate<Point3>     EvalPoint3;
        typedef EvalTemplate<Point4>     EvalPoint4;
        typedef EvalTemplate<Rect>       EvalRect;
        typedef EvalTemplate<RectF>      EvalRectF;
        typedef EvalTemplate<Vector2>    EvalVector2;
        typedef EvalTemplate<Vector3>    EvalVector3;
        typedef EvalTemplate<Vector4>    EvalVector4;
        typedef EvalTemplate<GameAsset*> EvalGameAsset;

        typedef SharedPointer<EvalBool>      EvalBoolPtr;
        typedef SharedPointer<EvalShortInt>  EvalShortIntPtr;
        typedef SharedPointer<EvalInt>       EvalIntPtr;
        typedef SharedPointer<EvalLongInt>   EvalLongIntPtr;
        typedef SharedPointer<EvalFloat>     EvalFloatPtr;
        typedef SharedPointer<EvalDouble>    EvalDoublePtr;
        typedef SharedPointer<EvalColor>     EvalColorPtr;
        typedef SharedPointer<EvalPoint2>    EvalPoint2Ptr;
        typedef SharedPointer<EvalPoint3>    EvalPoint3Ptr;
        typedef SharedPointer<EvalPoint4>    EvalPoint4Ptr;
        typedef SharedPointer<EvalRect>      EvalRectPtr;
        typedef SharedPointer<EvalRectF>     EvalRectFPtr;
        typedef SharedPointer<EvalVector2>   EvalVector2Ptr;
        typedef SharedPointer<EvalVector3>   EvalVector3Ptr;
        typedef SharedPointer<EvalVector4>   EvalVector4Ptr;
        typedef SharedPointer<EvalGameAsset> EvalGameAssetPtr;
    }

#   include <Bibim/Evals.inl>

#endif