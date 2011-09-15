#pragma once
#ifndef __BIBIM_WINDOW_H__
#define __BIBIM_WINDOW_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/Point.h>
#   include <Bibim/Signal.h>

    namespace Bibim
    {
        class Window : public GameModule
        {
            BBGameModuleClass('W', 'I', 'N', 'D');
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

                inline Signal<int>& MouseWheel();

            private:
                Signal<int> mouseWheel;
        };
    }

#   include <Bibim/Window.inl>

#endif