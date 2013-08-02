#include <Bibim/Config.h>
#include <Bibim/GraphicsDeviceBase.h>
#include <Bibim/Assert.h>
#include <algorithm>

namespace Bibim
{
    GraphicsDeviceBase::GraphicsDeviceBase()
        : window(nullptr),
          isReset(false)
    {
    }

    GraphicsDeviceBase::~GraphicsDeviceBase()
    {
        if (window)
            window->RemoveResizeEventListener(this);

        BBAssert(lostEventListeners.empty());
        BBAssert(restoreEventListeners.empty());
    }

    void GraphicsDeviceBase::SetWindow(Window* value)
    {
        if (window != value)
        {
            if (window)
                window->RemoveResizeEventListener(this);

            Finalize();

            window = value;

            if (window)
            {
                Initialize();
                window->AddResizeEventListener(this);
            }
        }
    }

    void GraphicsDeviceBase::AddLostEventListener(LostEventListener* listener)
    {
        BBAssertDebug(std::find(lostEventListeners.begin(), lostEventListeners.end(), listener) == lostEventListeners.end());
        lostEventListeners.push_back(listener);
    }

    void GraphicsDeviceBase::RemoveLostEventListener(LostEventListener* listener)
    {
        std::vector<LostEventListener*>::iterator it = std::find(lostEventListeners.begin(), lostEventListeners.end(), listener);
        if (it != lostEventListeners.end())
            lostEventListeners.erase(it);
    }

    void GraphicsDeviceBase::AddRestoreEventListener(RestoreEventListener* listener)
    {
        BBAssertDebug(std::find(restoreEventListeners.begin(), restoreEventListeners.end(), listener) == restoreEventListeners.end());
        restoreEventListeners.push_back(listener);
    }

    void GraphicsDeviceBase::RemoveRestoreEventListener(RestoreEventListener* listener)
    {
        std::vector<RestoreEventListener*>::iterator it = std::find(restoreEventListeners.begin(), restoreEventListeners.end(), listener);
        if (it != restoreEventListeners.end())
            restoreEventListeners.erase(it);
    }

    void GraphicsDeviceBase::Initialize()
    {
        std::vector<RestoreEventListener*> temporaryListeners = restoreEventListeners;
        for (std::vector<RestoreEventListener*>::const_iterator it = temporaryListeners.begin(); it != temporaryListeners.end(); it++)
            (*it)->OnGraphicsDeviceRestore(this);
    }

    void GraphicsDeviceBase::Finalize()
    {
        std::vector<LostEventListener*> temporaryListeners = lostEventListeners;
        for (std::vector<LostEventListener*>::const_reverse_iterator it = temporaryListeners.rbegin(); it != temporaryListeners.rend(); it++)
            (*it)->OnGraphicsDeviceLost(this);
    }

    void GraphicsDeviceBase::Reset()
    {
        if (isReset)
        {
            Finalize();
            Initialize();
            isReset = false;
        }
    }

    void GraphicsDeviceBase::OnWindowResized(Window* window)
    {
        BBAssert(GetWindow() == window);
        isReset = true;
    }
}