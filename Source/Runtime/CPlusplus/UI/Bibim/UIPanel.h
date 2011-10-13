#pragma once
#ifndef __BIBIM_UIPANEL_H__
#define __BIBIM_UIPANEL_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIVisual.h>
#   include <vector>

    namespace Bibim
    {
        class UIPanel : public UIVisual
        {
            BBComponentClass(UIPanel, UIVisual, 'U', 'P', 'N', 'L');
            public:
                typedef std::vector<UIVisualPtr> VisualCollection;

            public:
                UIPanel();
                explicit UIPanel(int childrenCapacity);
                virtual ~UIPanel();

                UIVisual* FindChild(const String& name, bool searchAllChildren) const;

                inline const VisualCollection& GetChildren() const;

                virtual bool IsPanel() const;

            protected:
                void Add(UIVisual* item);
                void Insert(int index, UIVisual* item);
                bool Remove(UIVisual* item);
                bool RemoveAt(int index);
                void RemoveAll();

                void DrawChildren(UIDrawingContext& context);

                virtual void OnDraw(UIDrawingContext& context);
                virtual void OnPick(UIPickingContext& context);
                virtual void OnChildAdded(UIVisual* child);
                virtual void OnChildRemoved(UIVisual* child);
                virtual void OnChildrenAdded(const VisualCollection& children);
                virtual void OnChildrenRemoved(const VisualCollection& children);

            private:
                void RemoveByIterator(VisualCollection::iterator it);

                void BringChildToFront(UIVisual* child);
                void SendChildToBack(UIVisual* child);

            private:
                VisualCollection children;

                friend class UIVisual;
        };
    }

#   include <Bibim/UIPanel.inl>

#endif