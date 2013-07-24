#pragma once
#ifndef __BIBIM_EVALSELECTORS_H__
#define __BIBIM_EVALSELECTORS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Evals.h>
#   include <Bibim/ComponentStreamReader.h>
#   include <vector>

    namespace Bibim
    {
        template <typename T, char a, char b, char c, char d>
        class EvalSelectorTemplate : public EvalTemplate<T>
        {
            BBComponentClass(EvalSelectorTemplate, EvalTemplate<T>, a, b, c, d);
            public:
                struct Case
                {
                    float Min;
                    float Max;
                    SharedPointer<EvalTemplate<T> > Item;

                    Case()
                        : Min(0.0f), Max(0.0f)
                    {
                    }

                    Case(float min, float max, EvalTemplate<T>* item)
                        : Min(min), Max(max), Item(item)
                    {
                    }
                };
                typedef std::vector<Case> CaseCollection;

            public:
                EvalSelectorTemplate() { }
                virtual ~EvalSelectorTemplate() { }

                virtual void Start()
                {
                    if (condition)
                        condition->Start();

                    for (typename CaseCollection::const_iterator it = cases.begin(); it != cases.end(); it++)
                    {
                        if ((*it).Item)
                            (*it).Item->Start();
                    }

                    if (defaultCase)
                        defaultCase->Start();
                }

                virtual void Stop()
                {
                    if (condition)
                        condition->Stop();

                    for (typename CaseCollection::const_iterator it = cases.begin(); it != cases.end(); it++)
                    {
                        if ((*it).Item)
                            (*it).Item->Stop();
                    }

                    if (defaultCase)
                        defaultCase->Stop();
                }

                virtual void Reset()
                {
                    if (condition)
                        condition->Reset();

                    for (typename CaseCollection::const_iterator it = cases.begin(); it != cases.end(); it++)
                    {
                        if ((*it).Item)
                            (*it).Item->Reset();
                    }

                    if (defaultCase)
                        defaultCase->Reset();
                }

                virtual T Evaluate(EvalContext& context)
                {
                    if (condition)
                    {
                        const float conditionValue = condition->Evaluate(context);
                        for (typename CaseCollection::const_iterator it = cases.begin(); it != cases.end(); it++)
                        {
                            const Case& item = (*it);
                            if (item.Min <= conditionValue && conditionValue <= item.Max)
                            {
                                if (item.Item)
                                    return item.Item->Evaluate(context);
                                else
                                    break;
                            }
                        }

                        if (defaultCase)
                            return defaultCase->Evaluate(context);
                    }

                    return T();
                }

                EvalFloat* GetCondition() const { return this->source; }
                void SetCondition(EvalFloat* value) { this->source = value; }

                const CaseCollection& GetCases() const { return cases; }
                void SetCases(const CaseCollection& value) { cases = value; }

                EvalTemplate<T>* GetDefaultCase() const { return defaultCase; }
                void SetDefaultCase(EvalTemplate<T>* value) { defaultCase = value; }

            private:
                SharedPointer<EvalFloat> condition;
                CaseCollection cases;
                SharedPointer<EvalTemplate<T> > defaultCase;
        };

        typedef EvalSelectorTemplate<bool,    'e', 'T', 'b', '_'> EvalBoolSelector;
        typedef EvalSelectorTemplate<short,   'e', 'T', 's', '_'> EvalShortIntSelector;
        typedef EvalSelectorTemplate<int,     'e', 'T', 'i', '_'> EvalIntSelector;
        typedef EvalSelectorTemplate<longint, 'e', 'T', 'l', '_'> EvalLongIntSelector;
        typedef EvalSelectorTemplate<float,   'e', 'T', 'f', '_'> EvalFloatSelector;
        typedef EvalSelectorTemplate<double,  'e', 'T', 'd', '_'> EvalDoubleSelector;
        typedef EvalSelectorTemplate<Color,   'e', 'T', 'c', '_'> EvalColorSelector;
        typedef EvalSelectorTemplate<Point2,  'e', 'T', 'p', '2'> EvalPoint2Selector;
        typedef EvalSelectorTemplate<Point3,  'e', 'T', 'p', '3'> EvalPoint3Selector;
        typedef EvalSelectorTemplate<Point4,  'e', 'T', 'p', '4'> EvalPoint4Selector;
        typedef EvalSelectorTemplate<Rect,    'e', 'T', 'r', '_'> EvalRectSelector;
        typedef EvalSelectorTemplate<RectF,   'e', 'T', 'R', 'f'> EvalRectFSelector;
        typedef EvalSelectorTemplate<Vector2, 'e', 'T', 'v', '2'> EvalVector2Selector;
        typedef EvalSelectorTemplate<Vector3, 'e', 'T', 'v', '3'> EvalVector3Selector;
        typedef EvalSelectorTemplate<Vector4, 'e', 'T', 'v', '4'> EvalVector4Selector;
        typedef EvalSelectorTemplate<GameAsset*, 'e', 'T', 'a', '_'> EvalGameAssetSelector;

        BBDeclareEvalClass(EvalBoolSelector);
        BBDeclareEvalClass(EvalShortIntSelector);
        BBDeclareEvalClass(EvalIntSelector);
        BBDeclareEvalClass(EvalLongIntSelector);
        BBDeclareEvalClass(EvalFloatSelector);
        BBDeclareEvalClass(EvalDoubleSelector);
        BBDeclareEvalClass(EvalColorSelector);
        BBDeclareEvalClass(EvalPoint2Selector);
        BBDeclareEvalClass(EvalPoint3Selector);
        BBDeclareEvalClass(EvalPoint4Selector);
        BBDeclareEvalClass(EvalRectSelector);
        BBDeclareEvalClass(EvalRectFSelector);
        BBDeclareEvalClass(EvalVector2Selector);
        BBDeclareEvalClass(EvalVector3Selector);
        BBDeclareEvalClass(EvalVector4Selector);
        BBDeclareEvalClass(EvalGameAssetSelector);

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        template <typename T, char a, char b, char c, char d>
        EvalSelectorTemplate<T, a, b, c, d>* EvalSelectorTemplate<T, a, b, c, d>::Clone() const
        {
            CloningContext context;
            return Clone(context);
        }

        template <typename T, char a, char b, char c, char d>
        EvalSelectorTemplate<T, a, b, c, d>* EvalSelectorTemplate<T, a, b, c, d>::Clone(CloningContext& context) const
        {
            This* clone = new This();
            context.Store(this, clone);
            clone->OnCopy(this, context);
            return clone;
        }

        template <typename T, char a, char b, char c, char d>
        void EvalSelectorTemplate<T, a, b, c, d>::OnRead(ComponentStreamReader& reader)
        {
            Base::OnRead(reader);
            condition = static_cast<EvalFloat*>(reader.ReadComponent());
            const int count = static_cast<int>(reader.ReadShortInt());
            cases.resize(count);
            for (int i = 0; i < count; i++)
            {
                cases[i].Min = reader.ReadFloat();
                cases[i].Max = reader.ReadFloat();
                cases[i].Item = static_cast<EvalTemplate<T>*>(reader.ReadComponent());
            }
            defaultCase = static_cast<EvalTemplate<T>*>(reader.ReadComponent());
        }

        template <typename T, char a, char b, char c, char d>
        void EvalSelectorTemplate<T, a, b, c, d>::OnCopy(const GameComponent* original, CloningContext& context)
        {
            Base::OnCopy(original, context);
            const This* o = static_cast<const This*>(original);
            condition = context.Clone(o->condition);
            cases.reserve(o->cases.size());
            for (typename CaseCollection::const_iterator it = o->cases.begin(); it != o->cases.end(); it++)
            {
                const Case& item = (*it);
                cases.push_back(Case(item.Min, item.Max, context.Clone(item.Item)));
            }
            defaultCase = context.Clone(o->defaultCase);
        }
    }

#endif