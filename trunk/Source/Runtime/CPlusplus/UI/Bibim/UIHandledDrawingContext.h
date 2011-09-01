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
                class IHandler
                {
                    protected:
                        virtual ~IHandler() { }

                        virtual void OnBegan(UIHandledDrawingContext& /*context*/) { }
                        virtual void OnEnded(UIHandledDrawingContext& /*context*/) { }
                        virtual void OnVisualBegan(UIHandledDrawingContext& /*context*/) { }
                        virtual void OnVisualEnded(UIHandledDrawingContext& /*context*/) { }

                        friend class UIHandledDrawingContext;
                };

                class BoundsVisualizer : public IHandler
                {
                    public:
                        static inline BoundsVisualizer* GetInstance();

                        static Color GetLineColor();
                        static void  SetLineColor(Color value);

                        static float GetLineWidth();
                        static void  SetLineWidth(float value);

                    protected:
                        virtual ~BoundsVisualizer();

                        virtual void OnVisualBegan(UIHandledDrawingContext& context);

                    private:
                        BoundsVisualizer();

                    private:
                        static Color LineColor;
                        static float LineWidth;
                };

            public:
                UIHandledDrawingContext(UIRenderer* renderer);
                UIHandledDrawingContext(UIRenderer* renderer, IHandler* handler);
                virtual ~UIHandledDrawingContext();

                inline IHandler* GetHandler() const;
                inline void SetHandler(IHandler* value);

            protected:
                virtual void OnBegan();
                virtual void OnEnded();
                virtual void OnVisit();

            private:
                IHandler* handler;
        };
    }

#   include <Bibim/UIHandledDrawingContext.inl>

#endif