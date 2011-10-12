#include <Bibim/PCH.h>
#include <Bibim/UIPanel.h>
#include <Bibim/Assert.h>
#include <Bibim/Math.h>
#include <Bibim/UIDrawingContext.h>
#include <Bibim/UIFrame.h>
#include <Bibim/UIPickingContext.h>
#include <Bibim/UIStreamReader.h>
#include <Bibim/UIVisual.h>
#include <algorithm>

namespace Bibim
{
    UIPanel::UIPanel()
    {
    }

    UIPanel::UIPanel(int childrenCapacity)
    {
        children.reserve(childrenCapacity);
    }

    UIPanel::~UIPanel()
    {
    }

    UIVisual* UIPanel::FindChild(const String& name, bool searchAllChildren) const
    {
        if (searchAllChildren)
        {
            for (VisualCollection::const_iterator it = children.begin(); it != children.end(); it++)
            {
                if ((*it)->GetName() == name)
                    return (*it);

                if ((*it)->IsPanel())
                {
                    if (UIVisual* found = static_cast<UIPanel*>((*it).GetPointee())->FindChild(name, true))
                        return found;
                }
            }
        }
        else
        {
            for (VisualCollection::const_iterator it = children.begin(); it != children.end(); it++)
            {
                if ((*it)->GetName() == name)
                    return (*it);
            }
        }

        return nullptr;
    }

    bool UIPanel::IsPanel() const
    {
        return true;
    }

    void UIPanel::Add(UIVisual* item)
    {
        Insert(children.size(), item);
    }

    void UIPanel::Insert(int index, UIVisual* item)
    {
        index = Math::Clamp(index, 0, static_cast<int>(children.size()));

        if (item->GetParent())
            item->GetParent()->Remove(item);

        BBAssertDebug(item->GetParent() == nullptr);

        item->SetParent(this);

        if (index < static_cast<int>(children.size()))
            children.insert(children.begin() + index, item);
        else
            children.push_back(item);

        OnChildAdded(item);
    }

    bool UIPanel::Remove(UIVisual* item)
    {
        VisualCollection::iterator it = std::find(children.begin(), children.end(), item);
        if (it != children.end())
        {
            RemoveByIterator(it);
            return true;
        }
        else
            return false;
    }

    bool UIPanel::RemoveAt(int index)
    {
        if (0 <= index && index < static_cast<int>(children.size()))
        {
            RemoveByIterator(children.begin() + index);
            return true;
        }
        else
            return false;
    }

    void UIPanel::RemoveByIterator(VisualCollection::iterator it)
    {
        BBAssertDebug(it != children.end() && (*it) != nullptr);

        UIVisualPtr child = (*it);
        children.erase(it);
        child->SetParent(nullptr);
        OnChildRemoved(child);
    }

    void UIPanel::RemoveAll()
    {
        VisualCollection removingChildren;
        removingChildren.swap(children);

        for (VisualCollection::iterator it = removingChildren.begin(); it != removingChildren.end(); it++)
            (*it)->SetParent(nullptr);

        OnChildrenRemoved(removingChildren);
    }

    void UIPanel::DrawChildren(UIDrawingContext& context)
    {
        for (VisualCollection::const_iterator it = children.begin(); it != children.end(); it++)
            context.DrawChild(*it);
    }

    void UIPanel::OnDraw(UIDrawingContext& context)
    {
        DrawChildren(context);
    }

    void UIPanel::OnPick(UIPickingContext& context)
    {
        if (context.Contains(context.GetCurrentClippedBounds()))
        {
            for (VisualCollection::const_reverse_iterator it = children.rbegin(); it != children.rend(); it++)
            {
                if (context.Pick(*it))
                    return;
            }

            context.SetResult(this);
        }
    }

    void UIPanel::OnChildAdded(UIVisual* /*child*/)
    {
    }

    void UIPanel::OnChildRemoved(UIVisual* /*child*/)
    {
    }

    void UIPanel::OnChildrenAdded(const VisualCollection& /*children*/)
    {
    }

    void UIPanel::OnChildrenRemoved(const VisualCollection& /*children*/)
    {
    }

    void UIPanel::BringChildToFront(UIVisual* child)
    {
        VisualCollection::iterator it = std::find(children.begin(), children.end(), child);
        BBAssert(it != children.end());
        if (it == children.end() - 1)
        {
            children.erase(it);
            children.push_back(child);
        }
    }

    void UIPanel::SendChildToBack(UIVisual* child)
    {
        VisualCollection::iterator it = std::find(children.begin(), children.end(), child);
        BBAssert(it != children.end());

        if (it != children.begin())
        {
            children.erase(it);
            children.insert(children.begin(), child);
        }
    }

    void UIPanel::Read(StreamReader& reader, UIPanel* o)
    {
        UIVisual::Read(reader, o);
        const int numberOfChildren = reader.ReadInt32();
        for (int i = 0; i < numberOfChildren; i++)
        {
        }
    }

    UIElement* UIPanel::Create(StreamReader& reader, UIElement* /*existingInstance*/)
    {
        UIPanel* o = new UIPanel();
        UIPanel::Read(reader, o);

        return o;
    }
}