#pragma once
#ifndef __BIBIM_UILIVEWINDOW_H__
#define __BIBIM_UILIVEWINDOW_H__

#include <Bibim/FWD.h>
#include <Bibim/UIWindow.h>
#include <vector>

namespace Bibim
{
    class UILiveWindow : public UIWindow
    {
        BBComponentClass(UILiveWindow, UIWindow, 'U', 'P', 'W', 'D');
        public:
            UILiveWindow();
            explicit UILiveWindow(int childrenCapacity);
            virtual ~UILiveWindow();

            void SnapLayout();

        protected:
            virtual void OnDraw(UIDrawingContext& context);

        private:
            struct LayoutSnapshot
            {
                const UIVisual* Child;
                float X;
                float Y;
                float Width;
                float Height;
                float Opacity;
            };

            const LayoutSnapshot* FindLayoutSnapshot(UIVisual* item) const;

        private:
            std::vector<LayoutSnapshot> layoutSnapshots;
            float layoutSnapTime;
            bool isLive;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////
}

BBBindLua(Bibim::UILiveWindow);

#endif