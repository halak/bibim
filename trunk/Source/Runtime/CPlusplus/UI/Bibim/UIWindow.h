#pragma once
#ifndef __BIBIM_UIWINDOW_H__
#define __BIBIM_UIWINDOW_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIPanel.h>
#   include <Bibim/Signal.h>
#   include <vector>

    namespace Bibim
    {
        class UIWindow : public UIPanel
        {
            BBUIElementClass('U', 'W', 'N', 'D');
            public:
                UIWindow();
                explicit UIWindow(int childrenCapacity);
                virtual ~UIWindow();

                inline void AddChild(UIVisual* item);
                inline void InsertChild(int index, UIVisual* item);
                inline bool RemoveChild(UIVisual* item);
                inline bool RemoveChildAt(int index);
                inline void RemoveAllChildren();
        };
    }

#   include <Bibim/UIWindow.inl>

#endif