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
                        virtual ~BoundsVisualizer();

                        virtual void OnVisualBegan(UIHandledDrawingContext& context);
                        virtual void OnVisualEnded(UIHandledDrawingContext& context);

                    private:
                        BoundsVisualizer();
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
    }

#   include <Bibim/UIHandledDrawingContext.inl>

#endif