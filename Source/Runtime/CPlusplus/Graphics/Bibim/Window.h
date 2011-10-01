#pragma once
#ifndef __BIBIM_WINDOW_H__
#define __BIBIM_WINDOW_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/Point.h>

    namespace Bibim
    {
        class Window : public GameModule
        {
            BBAbstractObjectClass(Window, GameModule);
            public:
                virtual ~Window();

                virtual void Close() = 0;

                virtual Point GetPosition() const = 0;
                virtual void  SetPosition(Point value) = 0;

                virtual Point GetSize() const = 0;
                virtual void  SetSize(Point value) = 0;

                virtual bool GetVisible() const = 0;
                virtual void SetVisible(bool value) = 0;

                virtual void* GetHandle() const = 0;

                inline int GetWheel() const;

            protected:
                inline Window();
                inline void SetWheel(int value);

            private:
                int wheelValue;
        };
    }

#   include <Bibim/Window.inl>

#endif