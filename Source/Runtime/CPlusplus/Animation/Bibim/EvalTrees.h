#pragma once
#ifndef __BIBIM_EVALTREES_H__
#define __BIBIM_EVALTREES_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameAsset.h>
#   include <Bibim/Evals.h>

    namespace Bibim
    {
        template <typename T, char a, char b, char c, char d>
        class EvalTreeTemplate : public GameAsset
        {
            BBSerializableAssetClass(EvalTreeTemplate, GameAsset, a, b, c, d);
            public:
                typedef EvalTemplate<T> Eval;

            public:
                EvalTreeTemplate();
                EvalTreeTemplate(Eval* root);
                virtual ~EvalTreeTemplate();

                Eval* GetRoot() const;
                void SetRoot(Eval* value);

            private:
                SharedPointer<Eval> root;
        };

        typedef EvalTreeTemplate<bool,         'e', 't', 'b', '_'> BoolEvalTree;
        typedef EvalTreeTemplate<short,        'e', 't', 's', '_'> ShortIntEvalTree;
        typedef EvalTreeTemplate<int,          'e', 't', 'i', '_'> IntEvalTree;
        typedef EvalTreeTemplate<longint,      'e', 't', 'l', '_'> LongIntEvalTree;
        typedef EvalTreeTemplate<float,        'e', 't', 'f', '_'> FloatEvalTree;
        typedef EvalTreeTemplate<double,       'e', 't', 'd', '_'> DoubleEvalTree;
        typedef EvalTreeTemplate<Color,        'e', 't', 'c', '_'> ColorEvalTree;
        typedef EvalTreeTemplate<Point2,       'e', 't', 'p', '2'> Point2EvalTree;
        typedef EvalTreeTemplate<Point3,       'e', 't', 'p', '3'> Point3EvalTree;
        typedef EvalTreeTemplate<Point4,       'e', 't', 'p', '4'> Point4EvalTree;
        typedef EvalTreeTemplate<Rect,         'e', 't', 'r', '_'> RectEvalTree;
        typedef EvalTreeTemplate<RectF,        'e', 't', 'R', 'f'> RectFEvalTree;
        typedef EvalTreeTemplate<Vector2,      'e', 't', 'v', '2'> Vector2EvalTree;
        typedef EvalTreeTemplate<Vector3,      'e', 't', 'v', '3'> Vector3EvalTree;
        typedef EvalTreeTemplate<Vector4,      'e', 't', 'v', '4'> Vector4EvalTree;
        typedef EvalTreeTemplate<GameAsset*,   'e', 't', 'a', '_'> GameAssetEvalTree;

        typedef SharedPointer<BoolEvalTree>      BoolEvalTreePtr;
        typedef SharedPointer<ShortIntEvalTree>  ShortIntEvalTreePtr;
        typedef SharedPointer<IntEvalTree>       IntEvalTreePtr;
        typedef SharedPointer<LongIntEvalTree>   LongIntEvalTreePtr;
        typedef SharedPointer<FloatEvalTree>     FloatEvalTreePtr;
        typedef SharedPointer<DoubleEvalTree>    DoubleEvalTreePtr;
        typedef SharedPointer<ColorEvalTree>     ColorEvalTreePtr;
        typedef SharedPointer<Point2EvalTree>    Point2EvalTreePtr;
        typedef SharedPointer<Point3EvalTree>    Point3EvalTreePtr;
        typedef SharedPointer<Point4EvalTree>    Point4EvalTreePtr;
        typedef SharedPointer<RectEvalTree>      RectEvalTreePtr;
        typedef SharedPointer<RectFEvalTree>     RectFEvalTreePtr;
        typedef SharedPointer<Vector2EvalTree>   Vector2EvalTreePtr;
        typedef SharedPointer<Vector3EvalTree>   Vector3EvalTreePtr;
        typedef SharedPointer<Vector4EvalTree>   Vector4EvalTreePtr;
        typedef SharedPointer<GameAssetEvalTree> GameAssetEvalTreePtr;
    }

#   include <Bibim/EvalTrees.inl>

#endif