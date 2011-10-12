#pragma once
#ifndef __BIBIM_UIWINDOW_H__
#define __BIBIM_UIWINDOW_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIPanel.h>
#   include <vector>

    namespace Bibim
    {
        class UIWindow : public UIPanel
        {
            BBCreatableObjectClass(UIWindow, UIPanel, UIElement, 'U', 'W', 'N', 'D');
            public:
                UIWindow();
                explicit UIWindow(int childrenCapacity);
                virtual ~UIWindow();

                inline void AddChild(UIVisual* item);
                inline void InsertChild(int index, UIVisual* item);
                inline bool RemoveChild(UIVisual* item);
                inline bool RemoveChildAt(int index);
                inline void RemoveAllChildren();

                virtual Vector2 GetDesiredSize();

                inline Vector2 GetFixedSize() const;
                inline void SetFixedSize(Vector2 value);

                inline bool GetFixedSizeUsed() const;
                inline void SetFixedSizeUsed(bool value);

            protected:
                static void Read(StreamReader& reader, UIWindow* o);

            private:
                Vector2 fixedSize;
                bool fixedSizeUsed;
        };
    }

#   include <Bibim/UIWindow.inl>

#endif