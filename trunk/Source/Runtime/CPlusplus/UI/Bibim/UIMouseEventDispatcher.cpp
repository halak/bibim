#include <Bibim/PCH.h>
#include <Bibim/UIMouseEventDispatcher.h>
#include <Bibim/UIDomain.h>
#include <Bibim/Mouse.h>
#include <Bibim/UIMouseButtonEventArgs.h>
#include <Bibim/UIMouseEventArgs.h>
#include <Bibim/UIMouseWheelEventArgs.h>
#include <Bibim/UIPickingContext.h>
#include <Bibim/UIWindow.h>
#include <algorithm>

namespace Bibim
{
    UIMouseEventDispatcher::UIMouseEventDispatcher()
        : domain(nullptr),
          device(nullptr),
          renderer(nullptr),
          capturedVisual(nullptr),
          lastTargetVisual(nullptr),
          lastMouseState(MouseState::Empty)
    {
    }

    UIMouseEventDispatcher::UIMouseEventDispatcher(UIDomain* domain, Mouse* device, UIRenderer* renderer)
        : domain(domain),
          device(device),
          renderer(renderer),
          capturedVisual(nullptr),
          lastTargetVisual(nullptr),
          lastMouseState(MouseState::Empty)
    {
    }

    UIMouseEventDispatcher::~UIMouseEventDispatcher()
    {
    }

    void UIMouseEventDispatcher::Reset()
    {
        capturedVisual.Reset();
        lastTargetVisual.Reset();
    }

    void UIMouseEventDispatcher::Update(float /*dt*/, int timestamp)
    {
        if (domain == nullptr ||
            device == nullptr ||
            renderer == nullptr ||
            GetStatus() != ActiveStatus ||
            Seal(timestamp))
            return;

        UIWindow* rootWindow = domain->GetRoot();
        if (rootWindow == nullptr)
            return;

        const MouseState& mouseState = device->GetState();
        UIPickingContext picker(renderer, Vector2(mouseState.Position.X, mouseState.Position.Y));

        struct Pick
        {
            static UIVisual* Do(UIPickingContext& context, UIWindow* rootWindow)
            {
                if (context.Pick(rootWindow))
                    return context.GetResult();
                else
                    return rootWindow;
            }
        };

        UIVisual* pickedVisual = nullptr;
        UIVisual* targetVisual = nullptr;

        if (capturedVisual)
            targetVisual = capturedVisual;
        else
        {
            pickedVisual = Pick::Do(picker, rootWindow);
            targetVisual = pickedVisual;
        }

        const UIMouseEventArgs baseArgs = UIMouseEventArgs(targetVisual,
                                                           mouseState.Position,
                                                           mouseState.IsLeftButtonPressed,
                                                           mouseState.IsRightButtonPressed,
                                                           mouseState.IsMiddleButtonPressed);

        if (targetVisual != lastTargetVisual)
        {
            // 가리키고 있는 Window가 달라지면,
            // 이전에 가리킨 Window와 그 부모들에게 MouseLeave Event를 발생시키고
            // 현재 가리키고 있는 Window와 그 부모들에게 MouseEnter Event를 발생시킵니다.
            // 물론 두 Window의 공통된 부모들에게는 아무 Event도 발생시키지 않습니다.

            cachedEnterVisuals.clear();
            cachedLeaveVisuals.clear();

            for (UIVisual* leaveVisual = lastTargetVisual; leaveVisual; leaveVisual = leaveVisual->GetParent())
                cachedLeaveVisuals.push_back(leaveVisual);
            for (UIVisual* enterVisual = targetVisual; enterVisual; enterVisual = enterVisual->GetParent())
            {
                const VisualVector::const_iterator it = std::find(cachedLeaveVisuals.begin(), cachedLeaveVisuals.end(), enterVisual);
                if (it == cachedLeaveVisuals.end())
                    cachedEnterVisuals.push_back(enterVisual);
                else
                {
                    cachedLeaveVisuals.resize(it - cachedLeaveVisuals.begin());
                    break;
                }
            }

            for (VisualVector::const_iterator it = cachedLeaveVisuals.begin(); it != cachedLeaveVisuals.end(); it++)
                (*it)->RaiseMouseLeaveEvent(baseArgs);

            for (VisualVector::const_iterator it = cachedEnterVisuals.begin(); it != cachedEnterVisuals.end(); it++)
                (*it)->RaiseMouseEnterEvent(baseArgs);
        }

        if (targetVisual && lastMouseState.Position != mouseState.Position)
            targetVisual->RaiseMouseMoveEvent(baseArgs);

        if (targetVisual)
        {
            if (mouseState.IsLeftButtonPressed)
            {
                if (lastMouseState.IsLeftButtonPressed)
                    targetVisual->RaiseMouseButtonPressingEvent(UIMouseButtonEventArgs(baseArgs, Key::MouseLeftButton));
                else
                {
                    capturedVisual = targetVisual;

                    if (targetVisual->GetFocusable())
                        domain->SetFocus(targetVisual);

                    targetVisual->RaiseMouseButtonDownEvent(UIMouseButtonEventArgs(baseArgs, Key::MouseLeftButton));
                }
            }
            else
            {
                if (lastMouseState.IsLeftButtonPressed)
                {
                    capturedVisual.Reset();

                    targetVisual->RaiseMouseButtonUpEvent(UIMouseButtonEventArgs(baseArgs, Key::MouseLeftButton));

                    if (pickedVisual == nullptr)
                        pickedVisual = Pick::Do(picker, rootWindow);

                    if (targetVisual == pickedVisual)
                        targetVisual->RaiseMouseClickEvent(baseArgs);
                }
            }

            if (mouseState.IsRightButtonPressed)
            {
                if (lastMouseState.IsRightButtonPressed)
                    targetVisual->RaiseMouseButtonPressingEvent(UIMouseButtonEventArgs(baseArgs, Key::MouseRightButton));
                else
                    targetVisual->RaiseMouseButtonDownEvent(UIMouseButtonEventArgs(baseArgs, Key::MouseRightButton));
            }
            else
            {
                if (lastMouseState.IsRightButtonPressed)
                    targetVisual->RaiseMouseButtonUpEvent(UIMouseButtonEventArgs(baseArgs, Key::MouseRightButton));
            }

            if (mouseState.IsMiddleButtonPressed)
            {
                if (lastMouseState.IsMiddleButtonPressed)
                    targetVisual->RaiseMouseButtonPressingEvent(UIMouseButtonEventArgs(baseArgs, Key::MouseMiddleButton));
                else
                    targetVisual->RaiseMouseButtonDownEvent(UIMouseButtonEventArgs(baseArgs, Key::MouseMiddleButton));
            }
            else
            {
                if (lastMouseState.IsMiddleButtonPressed)
                    targetVisual->RaiseMouseButtonUpEvent(UIMouseButtonEventArgs(baseArgs, Key::MouseMiddleButton));
            }

            const int wheelDelta = mouseState.Wheel - lastMouseState.Wheel;
            if (wheelDelta != 0)
                targetVisual->RaiseMouseWheelEvent(UIMouseWheelEventArgs(baseArgs, wheelDelta));
        }

        lastTargetVisual = targetVisual;
        lastMouseState = mouseState;
    }

    void UIMouseEventDispatcher::SetDomain(UIDomain* value)
    {
        if (domain != value)
        {
            domain = value;
            lastTargetVisual.Reset();
            lastMouseState = MouseState::Empty;
        }
    }

    void UIMouseEventDispatcher::SetDevice(Mouse* value)
    {
        if (device != value)
        {
            device = value;
            lastTargetVisual.Reset();
            lastMouseState = MouseState::Empty;
        }
    }
}