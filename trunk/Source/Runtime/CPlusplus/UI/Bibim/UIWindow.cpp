#include <Bibim/PCH.h>
#include <Bibim/UIWindow.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    BBImplementsComponent(UIWindow);
    
    UIWindow::UIWindow()
        : fixedSize(Vector2::Zero),
          fixedSizeUsed(false)
    {
    }

    UIWindow::UIWindow(int childrenCapacity)
        : UIPanel(childrenCapacity),
          fixedSize(Vector2::Zero),
          fixedSizeUsed(false)
    {
    }

    UIWindow::~UIWindow()
    {
    }

    Vector2 UIWindow::GetDesiredSize()
    {
        if (GetFixedSizeUsed())
            return GetFixedSize();
        else
            return UIVisual::GetDesiredSize();
    }

    void UIWindow::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void UIWindow::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        fixedSize = o->fixedSize;
        fixedSizeUsed = o->fixedSizeUsed;
    }
}