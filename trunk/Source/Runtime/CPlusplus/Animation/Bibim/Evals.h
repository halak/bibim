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
#   include <Bibim/RectF.h>
#   include <Bibim/Vector2.h>
#   include <Bibim/Vector3.h>
#   include <Bibim/Vector4.h>

    namespace Bibim
    {
        class EvalBase : public GameComponent
        {
            BBAbstractComponentClass(EvalBase, GameComponent);
            public:
                virtual ~EvalBase() { }

                virtual void Start() = 0;
                virtual void Stop()  = 0;
                virtual void Reset() = 0;

            protected:
                EvalBase();
        };

        template <typename T> class EvalTemplate : public EvalBase
        {
            BBAbstractComponentClass(EvalTemplate, EvalBase);
            public:
                virtual ~EvalTemplate() { }

                virtual void Reset() = 0;
                virtual T Evaluate(EvalContext& context) = 0;
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

#       define BBDeclareEvalClass(classname) typedef SharedPointer<classname> classname##Ptr;
        BBDeclareEvalClass(EvalBool);
        BBDeclareEvalClass(EvalShortInt);
        BBDeclareEvalClass(EvalInt);
        BBDeclareEvalClass(EvalLongInt);
        BBDeclareEvalClass(EvalFloat);
        BBDeclareEvalClass(EvalDouble);
        BBDeclareEvalClass(EvalColor);
        BBDeclareEvalClass(EvalPoint2);
        BBDeclareEvalClass(EvalPoint3);
        BBDeclareEvalClass(EvalPoint4);
        BBDeclareEvalClass(EvalRect);
        BBDeclareEvalClass(EvalRectF);
        BBDeclareEvalClass(EvalVector2);
        BBDeclareEvalClass(EvalVector3);
        BBDeclareEvalClass(EvalVector4);
        BBDeclareEvalClass(EvalGameAsset);
    }

#endif