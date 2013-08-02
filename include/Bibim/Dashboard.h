#pragma once
#ifndef __BIBIM_DASHBOARD_H__
#define __BIBIM_DASHBOARD_H__

#include <Bibim/FWD.h>
#include <Bibim/UIHandledDrawingContext.h>
#include <Bibim/IPEndPoint.h>
#include <sstream>

namespace Bibim
{
    class Dashboard : public UIHandledDrawingContext::Handler
    {
        public:
            Dashboard();
            Dashboard(IPEndPoint endPoint);
            ~Dashboard();

        protected:
            virtual void OnBegan(UIHandledDrawingContext& context, UIVisual* target);
            virtual void OnEnded(UIHandledDrawingContext& context, UIVisual* target);
            virtual void OnVisualBegan(UIHandledDrawingContext& context);
            virtual void OnVisualEnded(UIHandledDrawingContext& context);

        private:
            void Construct(IPEndPoint endPoint);
            void TryConnect();

            static void Jsonify(std::ostringstream& o, UIVisual* visual);

        private:
            SocketPtr socket;
            StreamPtr socketStream;

            std::ostringstream stringstream;
            void* selectedVisual;
            RectF selectedVisualBounds;
            RectF selectedVisualClippedBounds;
    };
}

#endif