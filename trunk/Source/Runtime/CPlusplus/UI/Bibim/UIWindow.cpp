#include <Bibim/PCH.h>
#include <Bibim/UIWindow.h>
#include <Bibim/UIStreamReader.h>

namespace Bibim
{
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

    void UIWindow::Read(StreamReader& reader, UIWindow* o)
    {
        UIPanel::Read(reader, o);
    }

    UIElement* UIWindow::Create(StreamReader& reader, UIElement* /*existingInstance*/)
    {
        UIWindow* o = new UIWindow();
        UIWindow::Read(reader, o);

        return o;
    }
}