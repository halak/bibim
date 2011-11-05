#pragma once
#ifndef __BIBIM_WINDOW_H__
#define __BIBIM_WINDOW_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/Point2.h>

    namespace Bibim
    {
        class Window : public GameModule
        {
            BBAbstractModuleClass(Window, GameModule);
            public:
                virtual ~Window();

                virtual void Close() = 0;

                virtual Point2 GetPosition() const = 0;
                virtual void   SetPosition(Point2 value) = 0;

                virtual Point2 GetSize() const = 0;
                virtual void   SetSize(Point2 value) = 0;

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