#include <Bibim/PCH.h>
#include <Bibim/UIWindow.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    BBImplementsComponent(UIWindow);
    
    UIWindow::UIWindow()
    {
    }

    UIWindow::UIWindow(int childrenCapacity)
        : UIPanel(childrenCapacity)
    {
    }

    UIWindow::~UIWindow()
    {
    }

    bool UIWindow::IsWindow() const
    {
        return true;
    }

    void UIWindow::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void UIWindow::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
    }
}