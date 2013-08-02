#pragma once
#ifndef __BIBIM_EVALCACHES_H__
#define __BIBIM_EVALCACHES_H__

#include <Bibim/FWD.h>
#include <Bibim/Evals.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    template <typename T, char a, char b, char c, char d>
    class EvalCacheTemplate : public EvalTemplate<T>
    {
        BBComponentClass(EvalCacheTemplate, EvalTemplate<T>, a, b, c, d);
        public:
            enum EvalCacheUpdateMode
            {
                UpdateAtStart,
                UpdateAtReset,
                UpdateAtEverytime,
            };

        public:
            EvalCacheTemplate()
                : value(),
                  source(nullptr),
                  updateMode(UpdateAtEverytime),
                  valueChanged(true)
            {
            }

            EvalCacheTemplate(EvalTemplate<T>* source)
                : value(),
                  source(source),
                  updateMode(UpdateAtEverytime),
                  valueChanged(true)
            {
            }

            virtual ~EvalCacheTemplate() { }

            virtual void Start()
            {
                if (source)
                    source->Start();

                if (updateMode == UpdateAtStart)
                    valueChanged = true;
            }

            virtual void Stop()
            {
                if (source)
                    source->Stop();
            }

            virtual void Reset()
            {
                if (source)
                    source->Reset();

                if (updateMode == UpdateAtReset)
                    valueChanged = true;
            }

            virtual T Evaluate(EvalContext& context)
            {
                if (updateMode == UpdateAtEverytime)
                    valueChanged = true;

                if (valueChanged)
                {
                    valueChanged = false;
                    if (source)
                        value = source->Evaluate(context);
                    else
                        value = T();
                }

                return value;
            }

            EvalTemplate<T>* GetSource() const { return source; }
            void SetSource(EvalTemplate<T>* value) { source = value; }

            EvalCacheUpdateMode GetUpdateMode() const { return updateMode; }
            void SetUpdateMode(EvalCacheUpdateMode value) { updateMode = value; }

        private:
            T value;
            SharedPointer<EvalTemplate<T> > source;
            EvalCacheUpdateMode updateMode;
            bool valueChanged;
    };

    typedef EvalCacheTemplate<bool,    'e', 'C', 'b', '_'> EvalBoolCache;
    typedef EvalCacheTemplate<short,   'e', 'C', 's', '_'> EvalShortIntCache;
    typedef EvalCacheTemplate<int,     'e', 'C', 'i', '_'> EvalIntCache;
    typedef EvalCacheTemplate<longint, 'e', 'C', 'l', '_'> EvalLongIntCache;
    typedef EvalCacheTemplate<float,   'e', 'C', 'f', '_'> EvalFloatCache;
    typedef EvalCacheTemplate<double,  'e', 'C', 'd', '_'> EvalDoubleCache;
    typedef EvalCacheTemplate<Color,   'e', 'C', 'c', '_'> EvalColorCache;
    typedef EvalCacheTemplate<Point2,  'e', 'C', 'p', '2'> EvalPoint2Cache;
    typedef EvalCacheTemplate<Point3,  'e', 'C', 'p', '3'> EvalPoint3Cache;
    typedef EvalCacheTemplate<Point4,  'e', 'C', 'p', '4'> EvalPoint4Cache;
    typedef EvalCacheTemplate<Rect,    'e', 'C', 'r', '_'> EvalRectCache;
    typedef EvalCacheTemplate<RectF,   'e', 'C', 'R', 'f'> EvalRectFCache;
    typedef EvalCacheTemplate<Vector2, 'e', 'C', 'v', '2'> EvalVector2Cache;
    typedef EvalCacheTemplate<Vector3, 'e', 'C', 'v', '3'> EvalVector3Cache;
    typedef EvalCacheTemplate<Vector4, 'e', 'C', 'v', '4'> EvalVector4Cache;

    BBDeclareEvalClass(EvalBoolCache);
    BBDeclareEvalClass(EvalShortIntCache);
    BBDeclareEvalClass(EvalIntCache);
    BBDeclareEvalClass(EvalLongIntCache);
    BBDeclareEvalClass(EvalFloatCache);
    BBDeclareEvalClass(EvalDoubleCache);
    BBDeclareEvalClass(EvalColorCache);
    BBDeclareEvalClass(EvalPoint2Cache);
    BBDeclareEvalClass(EvalPoint3Cache);
    BBDeclareEvalClass(EvalPoint4Cache);
    BBDeclareEvalClass(EvalRectCache);
    BBDeclareEvalClass(EvalRectFCache);
    BBDeclareEvalClass(EvalVector2Cache);
    BBDeclareEvalClass(EvalVector3Cache);
    BBDeclareEvalClass(EvalVector4Cache);

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename T, char a, char b, char c, char d>
    EvalCacheTemplate<T, a, b, c, d>* EvalCacheTemplate<T, a, b, c, d>::Clone() const
    {
        CloningContext context;
        return Clone(context);
    }

    template <typename T, char a, char b, char c, char d>
    EvalCacheTemplate<T, a, b, c, d>* EvalCacheTemplate<T, a, b, c, d>::Clone(CloningContext& context) const
    {
        This* clone = new This();
        context.Store(this, clone);
        clone->OnCopy(this, context);
        return clone;
    }

    template <typename T, char a, char b, char c, char d>
    void EvalCacheTemplate<T, a, b, c, d>::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        source = static_cast<EvalTemplate<T>*>(reader.ReadComponent());
        updateMode = static_cast<EvalCacheUpdateMode>(reader.ReadByte());
        valueChanged = true;
    }

    template <typename T, char a, char b, char c, char d>
    void EvalCacheTemplate<T, a, b, c, d>::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        value = o->value;
        source = context.Clone(o->source);
        updateMode = o->updateMode;
        valueChanged = o->valueChanged;
    }
}

#endif