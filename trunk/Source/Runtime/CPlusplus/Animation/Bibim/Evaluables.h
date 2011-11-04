#pragma once
#ifndef __BIBIM_EVALUABLES_H__
#define __BIBIM_EVALUABLES_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameComponent.h>
#   include <Bibim/Point.h>
#   include <Bibim/Range.h>
#   include <Bibim/Rect.h>
#   include <Bibim/Vector2.h>
#   include <Bibim/Vector3.h>
#   include <Bibim/Vector4.h>

    namespace Bibim
    {
        template <typename T> class EvaluableTemplate : public GameComponent
        {
            BBAbstractComponentClass(EvaluableTemplate, GameComponent);
            public:
                virtual ~EvaluableTemplate() { }

                virtual T Evaluate(EvaluationContext& context) = 0;
        };

        typedef EvaluableTemplate<bool>       EvaluableBool;
        typedef EvaluableTemplate<short>      EvaluableShortInt;
        typedef EvaluableTemplate<int>        EvaluableInt;
        typedef EvaluableTemplate<int64>      EvaluableLongInt;
        typedef EvaluableTemplate<float>      EvaluableFloat;
        typedef EvaluableTemplate<double>     EvaluableDouble;
        typedef EvaluableTemplate<Point>      EvaluablePoint;
        typedef EvaluableTemplate<Rect>       EvaluableRect;
        typedef EvaluableTemplate<RectF>      EvaluableRectF;
        typedef EvaluableTemplate<Vector2>    EvaluableVector2;
        typedef EvaluableTemplate<Vector3>    EvaluableVector3;
        typedef EvaluableTemplate<Vector4>    EvaluableVector4;
        typedef EvaluableTemplate<GameAsset*> EvaluableGameAsset;

        typedef SharedPointer<EvaluableBool>      EvaluableBoolPtr;
        typedef SharedPointer<EvaluableShortInt>  EvaluableShortIntPtr;
        typedef SharedPointer<EvaluableInt>       EvaluableIntPtr;
        typedef SharedPointer<EvaluableLongInt>   EvaluableLongIntPtr;
        typedef SharedPointer<EvaluableFloat>     EvaluableFloatPtr;
        typedef SharedPointer<EvaluableDouble>    EvaluableDoublePtr;
        typedef SharedPointer<EvaluablePoint>     EvaluablePointPtr;
        typedef SharedPointer<EvaluableRect>      EvaluableRectPtr;
        typedef SharedPointer<EvaluableRectF>     EvaluableRectFPtr;
        typedef SharedPointer<EvaluableVector2>   EvaluableVector2Ptr;
        typedef SharedPointer<EvaluableVector3>   EvaluableVector3Ptr;
        typedef SharedPointer<EvaluableVector4>   EvaluableVector4Ptr;
        typedef SharedPointer<EvaluableGameAsset> EvaluableGameAssetPtr;
    }

#endif