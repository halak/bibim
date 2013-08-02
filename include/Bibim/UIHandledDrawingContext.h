#pragma once
#ifndef __BIBIM_UIHANDLEDDRAWINGCONTEXT_H__
#define __BIBIM_UIHANDLEDDRAWINGCONTEXT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIDrawingContext.h>

    namespace Bibim
    {
        class UIHandledDrawingContext : public UIDrawingContext
        {
            public:
                class Handler
                {
                    protected:
                        virtual ~Handler() { }

                        virtual void OnBegan(UIHandledDrawingContext& /*context*/, UIVisual* /*root*/) { }
                        virtual void OnEnded(UIHandledDrawingContext& /*context*/, UIVisual* /*root*/) { }
                        virtual void OnVisualBegan(UIHandledDrawingContext& /*context*/) { }
                        virtual void OnVisualEnded(UIHandledDrawingContext& /*context*/) { }

                        friend class UIHandledDrawingContext;
                };

                class BoundsVisualizer : public Handler
                {
                    public:
                        static inline BoundsVisualizer* GetInstance();

                    protected:
                        BoundsVisualizer();
                        virtual ~BoundsVisualizer();

                        virtual void OnVisualBegan(UIHandledDrawingContext& context);
                        virtual void OnVisualEnded(UIHandledDrawingContext& context);
                };

            public:
                UIHandledDrawingContext(UIRenderer* renderer);
                UIHandledDrawingContext(UIRenderer* renderer, Handler* handler);
                virtual ~UIHandledDrawingContext();

                inline Handler* GetHandler() const;
                inline void SetHandler(Handler* value);

            protected:
                virtual void OnBegan(UIVisual* root);
                virtual void OnEnded(UIVisual* root);
                virtual void OnVisit();

            private:
                Handler* handler;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        UIHandledDrawingContext::Handler* UIHandledDrawingContext::GetHandler() const
        {
            return handler;
        }

        void UIHandledDrawingContext::SetHandler(Handler* value)
        {
            handler = value;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        UIHandledDrawingContext::BoundsVisualizer* UIHandledDrawingContext::BoundsVisualizer::GetInstance()
        {
            static BoundsVisualizer Instance;
            return &Instance;
        }
    }

#endif