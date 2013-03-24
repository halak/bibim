#include <Bibim/PCH.h>
#include <Bibim/UIPanel.h>
#include <Bibim/Assert.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Math.h>
#include <Bibim/UIDrawingContext.h>
#include <Bibim/UIPickingContext.h>
#include <Bibim/UIVisual.h>
#include <algorithm>

namespace Bibim
{
    BBImplementsComponent(UIPanel);

    UIPanel::UIPanel()
    {
    }

    UIPanel::UIPanel(int childrenCapacity)
    {
        children.reserve(childrenCapacity);
    }

    UIPanel::~UIPanel()
    {
        VisualCollection removingChildren;
        removingChildren.swap(children);

        for (VisualCollection::iterator it = removingChildren.begin(); it != removingChildren.end(); it++)
            (*it)->SetParent(nullptr);
    }

    void UIPanel::ShowChildren()
    {
        for (VisualCollection::iterator it = children.begin(); it != children.end(); it++)
            (*it)->Show();
    }

    void UIPanel::HideChildren()
    {
        for (VisualCollection::iterator it = children.begin(); it != children.end(); it++)
            (*it)->Hide();
    }

    UIVisual* UIPanel::FindChild(const String& name, bool searchAllChildren) const
    {
        return FindChildByChars(name.CStr(), name.GetLength(), searchAllChildren);
    }

    UIVisual* UIPanel::FindChildByChars(const char* name, bool searchAllChildren) const
    {
        if (name)
            return FindChildByChars(name, String::CharsLength(name), searchAllChildren);
        else
            return nullptr;
    }

    UIVisual* UIPanel::FindChildByChars(const char* name, int length, bool searchAllChildren) const
    {
        if (name == nullptr || length == 0)
            return nullptr;

        for (VisualCollection::const_iterator it = children.begin(); it != children.end(); it++)
        {
            if ((*it)->GetName().Equals(name, length))
                return (*it);
        }

        if (searchAllChildren)
        {
            for (VisualCollection::const_iterator it = children.begin(); it != children.end(); it++)
            {
                if ((*it)->IsPanel())
                {
                    if (UIVisual* found = StaticCast<UIPanel>(*it)->FindChildByChars(name, true))
                        return found;
                }
            }
        }

        return nullptr;
    }

    int UIPanel::GetChildIndex(UIVisual* item) const
    {
        if (item == nullptr || item->GetParent() != this)
            return -1;

        const int count = GetNumberOfChildren();
        for (int i = 0; i < count; i++)
        {
            if (children[i] == item)
                return i;
        }

        return -1;
    }

    bool UIPanel::IsPanel() const
    {
        return true;
    }

    bool UIPanel::IsAncestorOf(UIVisual* item) const
    {
        while (item)
        {
            if (item == this)
                return true;

            item = item->GetParent();
        }

        return false;
    }

    void UIPanel::Add(UIVisual* item)
    {
        if (item == nullptr)
            return;

        UIVisualPtr sharedItem = item;

        const int zOrder = item->GetZOrder();
        const int count = static_cast<int>(children.size());
        for (int i = count - 1; i >= 0; i--)
        {
            if (zOrder >= children[i]->GetZOrder())
            {
                Insert(i + 1, item);
                return;
            }
        }

        Insert(0, item);
    }

    void UIPanel::Insert(int index, UIVisual* item)
    {
        UIVisualPtr sharedItem = item;

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

    void UIPanel::DrawChild(UIDrawingContext& context, UIVisual* child)
    {
        BBAssertDebug(child && child->GetParent() == this);

        context.DrawChild(child);
    }

    void UIPanel::DrawChildren(UIDrawingContext& context)
    {
        for (VisualCollection::const_iterator it = children.begin(); it != children.end(); it++)
            context.DrawChild(*it);
    }

    void UIPanel::DrawChildren(UIDrawingContext& context, int startIndex, int count)
    {
        count = Math::Min(count, static_cast<int>(children.size()) - startIndex);
        VisualCollection::const_iterator it = children.begin() + startIndex;
        for (int i = 0; i < count; i++)
            context.DrawChild(*it++);
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
                if (context.PickChild(*it))
                    return;
            }

            if (GetPickable())
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

    void UIPanel::OnChildZOrderChanged(UIVisual* child, int old)
    {
        VisualCollection::iterator it = std::find(children.begin(), children.end(), child);
        BBAssert(it != children.end());

        const int zOrder = child->GetZOrder();
        if (zOrder < old)
        {
            if (it == children.begin()) // 이미 맨 뒤에 있으므로 옮길 필요가 없습니다.
                return;

            UIVisualPtr lockedChild = child;

            do
            {
                UIVisual* next = *(it - 1);
                if (zOrder < next->GetZOrder())
                {
                    (*it) = next;
                    it--;
                }
                else
                {
                    (*it) = lockedChild;
                    return;
                }
            } while (it != children.begin());

            BBAssertDebug(it == children.begin());
            (*it) = lockedChild;
        }
        else
        {
            BBAssertDebug(child->GetZOrder() > old);

            if (it + 1 == children.end()) // 이미 맨 앞에 있으므로 옮길 필요가 없습니다.
                return;

            UIVisualPtr lockedChild = child;

            do
            {
                UIVisual* next = *(it + 1);
                if (zOrder > next->GetZOrder())
                {
                    (*it) = next;
                    it++;
                }
                else
                {
                    (*it) = lockedChild;
                    return;
                }
            } while (it + 1 != children.end());

            BBAssertDebug(it + 1 == children.end());
            (*it) = lockedChild;
        }
    }

    void UIPanel::BringChildToFront(UIVisual* child)
    {
        VisualCollection::iterator it = std::find(children.begin(), children.end(), child);
        BBAssert(it != children.end());

        if (it + 1 == children.end())
            return;

        UIVisualPtr lockedChild = child;
        const int zOrder = child->GetZOrder();

        do
        {
            UIVisual* next = *(it + 1);
            if (zOrder == next->GetZOrder())
            {
                (*it) = next;
                it++;
            }
            else
            {
                (*it) = lockedChild;
                return;
            }

        } while (it + 1 != children.end());

        BBAssertDebug(it + 1 == children.end());
        (*it) = lockedChild;
    }

    void UIPanel::SendChildToBack(UIVisual* child)
    {
        VisualCollection::iterator it = std::find(children.begin(), children.end(), child);
        BBAssert(it != children.end());

        if (it == children.begin())
            return;

        UIVisualPtr lockedChild = child;
        const int zOrder = child->GetZOrder();

        do
        {
            UIVisual* next = *(it - 1);
            if (zOrder == next->GetZOrder())
            {
                (*it) = next;
                it--;
            }
            else
            {
                (*it) = lockedChild;
                return;
            }

        } while (it != children.begin());

        BBAssertDebug(it == children.begin());
        (*it) = lockedChild;
    }

    void UIPanel::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        const int numberOfChildren = reader.ReadInt();
        for (int i = 0; i < numberOfChildren; i++)
        {
            Insert(children.size(), static_cast<UIVisual*>(reader.ReadComponent()));
        }
    }

    void UIPanel::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        children.reserve(o->children.size());
        for (VisualCollection::const_iterator it = o->children.begin(); it != o->children.end(); it++)
            Insert(children.size(), context.Clone(*it));
    }
}