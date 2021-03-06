#include <Bibim/Config.h>
#if (defined(BIBIM_PLATFORM_MOBILE))

#include <Bibim/GameWindow.Mobile.h>

namespace Bibim
{
    GameWindow::GameWindow()
    {
    }

    GameWindow::~GameWindow()
    {
        Close();
    }

    void GameWindow::MoveToScreenCenter()
    {
    }

    void GameWindow::Close()
    {
    }

    const String& GameWindow::GetTitle() const
    {
        return title;
    }

    void GameWindow::SetTitle(const String& value)
    {
        title = value;
    }

    Point2 GameWindow::GetPosition() const
    {
        return Point2::Zero;
    }

    void GameWindow::SetPosition(Point2 /*value*/)
    {
    }

    Point2 GameWindow::GetSize() const
    {
        return size;
    }

    void GameWindow::SetSize(Point2 value)
    {
        if (size != value)
        {
            size = value;
            RaiseResizedEvent();
        }
    }

    bool GameWindow::GetVisible() const
    {
        return true;
    }

    void GameWindow::SetVisible(bool /*value*/)
    {
    }

    bool GameWindow::GetFullscreenStyle() const
    {
        return true;
    }

    void GameWindow::SetFullscreenStyle(bool /*value*/)
    {
    }

    bool GameWindow::IsForeground() const
    {
        return true;
    }
    
    void* GameWindow::GetHandle() const
    {
        return nullptr;
    }

    void* GameWindow::GetDisplayHandle() const
    {
        return nullptr;
    }

    void GameWindow::AddDropFileEventListener(DropFileEventListener* /*listener*/)
    {
    }

    void GameWindow::RemoveDropFileEventListener(DropFileEventListener* /*listener*/)
    {
    }

    void GameWindow::OnCreated()
    {
    }

    void GameWindow::OnDestroy()
    {
    }

    void GameWindow::OnMouseWheel(int delta)
    {
    }

    void GameWindow::OnSnapShot()
    {
    }

    bool GameWindow::OnCommand(int /*commandID*/, int /*controlID*/, void* /*handle*/)
    {
        return false;
    }

    bool GameWindow::OnPaint()
    {
        return false;
    }
}

#endif