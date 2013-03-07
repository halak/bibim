#pragma once
#ifndef __BIBIM_GAMEWINDOW_ANDROID_H__
#define __BIBIM_GAMEWINDOW_ANDROID_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Window.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
        class GameWindow : public Window
        {
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

                bool GetActive() const;

                virtual void* GetHandle() const;
                virtual void* GetDisplayHandle() const;

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

#   include <Bibim/GameWindow.Android.inl>

#endif