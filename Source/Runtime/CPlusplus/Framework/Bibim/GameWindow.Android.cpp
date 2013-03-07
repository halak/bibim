#include <Bibim/PCH.h>
#include <Bibim/GameWindow.Android.h>

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
        size = value;
    }

    bool GameWindow::GetVisible() const
    {
        return true;
    }

    void GameWindow::SetVisible(bool /*value*/)
    {
    }

    bool GameWindow::GetActive() const
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