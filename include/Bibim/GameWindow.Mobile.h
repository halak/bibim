#pragma once
#ifndef __BIBIM_GAMEWINDOW_MOBILE_H__
#define __BIBIM_GAMEWINDOW_MOBILE_H__

#include <Bibim/FWD.h>
#if (defined(BIBIM_PLATFORM_MOBILE))

#include <Bibim/Window.h>
#include <Bibim/String.h>

namespace Bibim
{
    class GameWindow : public Window
    {
        BBModuleClass(GameWindow, Window, 'G', 'W', 'I', 'N');
        public:
            class DropFileEventListener
            {
                public:
                    virtual ~DropFileEventListener() { }

                    virtual void OnWindowFileDropped(Window* window, const char* filename) = 0;
            };

        public:
            GameWindow();

            void MoveToScreenCenter();

            virtual void Close();

            const String& GetTitle() const;
            void SetTitle(const String& value);

            virtual Point2 GetPosition() const;
            virtual void   SetPosition(Point2 value);

            virtual Point2 GetSize() const;
            virtual void   SetSize(Point2 value);

            virtual bool GetVisible() const;
            virtual void SetVisible(bool value);

            bool GetFullscreenStyle() const;
            void SetFullscreenStyle(bool value);

            bool IsForeground() const;

            virtual void* GetHandle() const;
            virtual void* GetDisplayHandle() const;

            void AddDropFileEventListener(DropFileEventListener* listener);
            void RemoveDropFileEventListener(DropFileEventListener* listener);

        protected:
            virtual ~GameWindow();

        protected:
            virtual void OnCreated();
            virtual void OnDestroy();
            virtual void OnMouseWheel(int delta);
            virtual void OnSnapShot();
            virtual bool OnCommand(int commandID, int controlID, void* handle);
            virtual bool OnPaint();

        private:
            String title;
            Point2 size;
    };
}

#endif
#endif