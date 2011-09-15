#pragma once
#ifndef __BIBIM_GAMEWINDOW_WINDOWS_H__
#define __BIBIM_GAMEWINDOW_WINDOWS_H__

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

                virtual Point GetPosition() const;
                virtual void  SetPosition(Point value);

                virtual Point GetSize() const;
                virtual void  SetSize(Point value);

                virtual bool GetVisible() const;
                virtual void SetVisible(bool value);

                bool GetActive() const;

                virtual void* GetHandle() const;

            protected:
                virtual ~GameWindow();

            protected:
                virtual void OnCreated();
                virtual void OnDestroy();
                virtual void OnMouseWheel(int delta);

            private:
                void CreateHandle();

            private:
                void* handle;
                String title;
                Point position;
                Point size;
                bool visible;

                struct Internal;
        };
    }

#   include <Bibim/GameWindow.Windows.inl>

#endif