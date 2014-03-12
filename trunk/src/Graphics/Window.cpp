#include <Bibim/Config.h>
#include <Bibim/Window.h>
#include <Bibim/Assert.h>
#include <algorithm>

namespace Bibim
{
    Window::~Window()
    {
        BBAssert(resizeEventListeners.empty());
        BBAssert(mouseEventListeners.empty());
        BBAssert(keyboardEventListeners.empty());
    }

    void Window::AddResizeEventListener(ResizeEventListener* listener)
    {
        std::vector<ResizeEventListener*>::iterator it = std::find(resizeEventListeners.begin(),
                                                                   resizeEventListeners.end(),
                                                                   listener);
        if (it == resizeEventListeners.end())
            resizeEventListeners.push_back(listener);
    }

    void Window::RemoveResizeEventListener(ResizeEventListener* listener)
    {
        std::vector<ResizeEventListener*>::iterator it = std::find(resizeEventListeners.begin(),
                                                                   resizeEventListeners.end(),
                                                                   listener);
        if (it != resizeEventListeners.end())
            resizeEventListeners.erase(it);
    }

    void Window::AddMouseEventListener(MouseEventListener* listener)
    {
        std::vector<MouseEventListener*>::iterator it = std::find(mouseEventListeners.begin(),
                                                                   mouseEventListeners.end(),
                                                                   listener);
        if (it == mouseEventListeners.end())
            mouseEventListeners.push_back(listener);
    }

    void Window::RemoveMouseEventListener(MouseEventListener* listener)
    {
        std::vector<MouseEventListener*>::iterator it = std::find(mouseEventListeners.begin(),
                                                                  mouseEventListeners.end(),
                                                                  listener);
        if (it != mouseEventListeners.end())
            mouseEventListeners.erase(it);
    }

    void Window::AddKeyboardEventListener(KeyboardEventListener* listener)
    {
        std::vector<KeyboardEventListener*>::iterator it = std::find(keyboardEventListeners.begin(),
                                                                     keyboardEventListeners.end(),
                                                                     listener);
        if (it == keyboardEventListeners.end())
            keyboardEventListeners.push_back(listener);
    }

    void Window::RemoveKeyboardEventListener(KeyboardEventListener* listener)
    {
        std::vector<KeyboardEventListener*>::iterator it = std::find(keyboardEventListeners.begin(),
                                                                     keyboardEventListeners.end(),
                                                                     listener);
        if (it != keyboardEventListeners.end())
            keyboardEventListeners.erase(it);
    }

    void Window::RaiseResizedEvent()
    {
        for (std::vector<ResizeEventListener*>::iterator it = resizeEventListeners.begin(); it != resizeEventListeners.end(); ++it)
            (*it)->OnWindowResized(this);
    }

    void Window::RaiseMouseMoveEvent(int x, int y)
    {
        for (std::vector<MouseEventListener*>::iterator it = mouseEventListeners.begin(); it != mouseEventListeners.end(); ++it)
            (*it)->OnMouseMove(this, x, y);
    }

    void Window::RaiseMouseLeftButtonDownEvent(int x, int y)
    {
        for (std::vector<MouseEventListener*>::iterator it = mouseEventListeners.begin(); it != mouseEventListeners.end(); ++it)
            (*it)->OnMouseLeftButtonDown(this, x, y);
    }

    void Window::RaiseMouseLeftButtonUpEvent(int x, int y)
    {
        for (std::vector<MouseEventListener*>::iterator it = mouseEventListeners.begin(); it != mouseEventListeners.end(); ++it)
            (*it)->OnMouseLeftButtonUp(this, x, y);
    }

    void Window::RaiseMouseMiddleButtonDownEvent(int x, int y)
    {
        for (std::vector<MouseEventListener*>::iterator it = mouseEventListeners.begin(); it != mouseEventListeners.end(); ++it)
            (*it)->OnMouseMiddleButtonDown(this, x, y);
    }

    void Window::RaiseMouseMiddleButtonUpEvent(int x, int y)
    {
        for (std::vector<MouseEventListener*>::iterator it = mouseEventListeners.begin(); it != mouseEventListeners.end(); ++it)
            (*it)->OnMouseMiddleButtonUp(this, x, y);
    }

    void Window::RaiseMouseRightButtonDownEvent(int x, int y)
    {
        for (std::vector<MouseEventListener*>::iterator it = mouseEventListeners.begin(); it != mouseEventListeners.end(); ++it)
            (*it)->OnMouseRightButtonDown(this, x, y);
    }

    void Window::RaiseMouseRightButtonUpEvent(int x, int y)
    {
        for (std::vector<MouseEventListener*>::iterator it = mouseEventListeners.begin(); it != mouseEventListeners.end(); ++it)
            (*it)->OnMouseRightButtonUp(this, x, y);
    }

    void Window::RaiseMouseWheelEvent(int value)
    {
        for (std::vector<MouseEventListener*>::iterator it = mouseEventListeners.begin(); it != mouseEventListeners.end(); ++it)
            (*it)->OnMouseWheel(this, value);
    }

    void Window::RaiseKeyDownEvent(Key::Code code)
    {
        for (std::vector<KeyboardEventListener*>::iterator it = keyboardEventListeners.begin(); it != keyboardEventListeners.end(); ++it)
            (*it)->OnKeyDown(this, code);
    }

    void Window::RaiseKeyUpEvent(Key::Code code)
    {
        for (std::vector<KeyboardEventListener*>::iterator it = keyboardEventListeners.begin(); it != keyboardEventListeners.end(); ++it)
            (*it)->OnKeyUp(this, code);
    }
}