#pragma once
#ifndef __BIBIM_DASHBOARD_H__
#define __BIBIM_DASHBOARD_H__

#include <Bibim/FWD.h>
#include <Bibim/UIHandledDrawingContext.h>
#include <Bibim/Log.h>
#include <Bibim/Color.h>
#include <Bibim/IPEndPoint.h>
#include <Bibim/FontString.h>
#include <deque>
#include <sstream>

namespace Bibim
{
    class Dashboard : public UIHandledDrawingContext::Handler,
                      public Log::Listener
    {
        public:
            Dashboard();
            Dashboard(IPEndPoint endPoint);
            ~Dashboard();

            void Initialize(GameModuleTree* modules);
            void Finalize();

            void BeginFrame();
            void EndFrame();

        protected:
            virtual void OnBegan(UIHandledDrawingContext& context, UIVisual* target);
            virtual void OnEnded(UIHandledDrawingContext& context, UIVisual* target);
            virtual void OnVisualBegan(UIHandledDrawingContext& context);
            virtual void OnVisualEnded(UIHandledDrawingContext& context);

            virtual void Error(const char* category, const char* message);
            virtual void Warning(const char* category, const char* message);
            virtual void Information(const char* category, const char* message);

        private:
            void Construct(IPEndPoint endPoint);
            void TryConnect();

            void AddLogNotification(Color color, const char* category, const char* message);

            static void Jsonify(std::ostringstream& o, UIVisual* visual);

            struct Notification
            {
                Color TextColor;
                FontString Text;
            };
            typedef std::deque<Notification> NotificationCollection;

        private:
            SocketPtr socket;
            StreamPtr socketStream;

            FontPtr font;
            int fontRevision;
            NotificationCollection notifications;

            std::ostringstream stringstream;
            void* selectedVisual;
            RectF selectedVisualBounds;
            RectF selectedVisualClippedBounds;
    };
}

#endif