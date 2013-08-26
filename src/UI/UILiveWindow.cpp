#include <Bibim/Config.h>
#include <Bibim/UILiveWindow.h>
#include <Bibim/Clock.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Ease.h>
#include <Bibim/Math.h>

namespace Bibim
{
    BBImplementsComponent(UILiveWindow);
    
    UILiveWindow::UILiveWindow()
        : layoutSnapTime(0.0f)
    {
    }

    UILiveWindow::UILiveWindow(int childrenCapacity)
        : UIWindow(childrenCapacity),
          layoutSnapTime(0.0f)
    {
    }

    UILiveWindow::~UILiveWindow()
    {
    }

    void UILiveWindow::SnapLayout()
    {
        const VisualCollection& children = GetChildren();

        layoutSnapshots.clear();
        layoutSnapshots.reserve(children.size());

        for (VisualCollection::const_iterator it = children.begin(); it != children.end(); it++)
        {
            const UIVisual* child = (*it);

            LayoutSnapshot item;
            item.Child = child;
            item.X = child->GetX();
            item.Y = child->GetY();
            item.Width = child->GetWidth();
            item.Height = child->GetHeight();
            item.Opacity = child->GetOpacity();
            layoutSnapshots.push_back(item);
        }

        layoutSnapTime = Clock::GetCurrent();
    }
    
    void UILiveWindow::OnDraw(UIDrawingContext& context)
    {
        if (layoutSnapshots.empty())
        {
            Base::OnDraw(context);
            return;
        }

        const float time = (Clock::GetCurrent() - layoutSnapTime);
        const float t = Ease::InOutSinusoidal(Math::Clamp(time / 0.3f));

        const VisualCollection& children = GetChildren();
        for (VisualCollection::const_iterator it = children.begin(); it != children.end(); it++)
        {
            UIVisual* child = (*it);
            if (const UILiveWindow::LayoutSnapshot* snapshot = FindLayoutSnapshot(child))
            {
                const float x = child->GetX();
                const float y = child->GetY();
                const float width = child->GetWidth();
                const float height = child->GetHeight();
                const float opacity = child->GetOpacity();

                child->SetXY(Math::Lerp(snapshot->X, x, t),
                             Math::Lerp(snapshot->Y, y, t));
                child->SetSize(Math::Lerp(snapshot->Width, width, t),
                               Math::Lerp(snapshot->Height, height, t));
                child->SetOpacity(Math::Lerp(snapshot->Opacity, opacity, t));

                DrawChild(context, child);

                child->SetXY(x, y);
                child->SetSize(width, height);
                child->SetOpacity(opacity);
            }
            else
                DrawChild(context, child);
        }
 
        if (t >= 1.0f)
            layoutSnapshots.clear();
    }

    const UILiveWindow::LayoutSnapshot* UILiveWindow::FindLayoutSnapshot(UIVisual* item) const
    {
        for (std::vector<LayoutSnapshot>::const_iterator it = layoutSnapshots.begin(); it != layoutSnapshots.end(); it++)
        {
            if ((*it).Child == item)
                return &(*it);
        }

        return nullptr;
    }

    void UILiveWindow::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void UILiveWindow::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
    }
}