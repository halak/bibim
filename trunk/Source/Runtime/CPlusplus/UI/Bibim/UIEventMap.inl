namespace Bibim
{
    UIAppEventDispatcher* UIEventMap::GetEventDispatcher() const
    {
        return eventDispatcher;
    }

    UIAsyncEventQueue* UIEventMap::GetAsyncEventQueue() const
    {
        return asyncEventQueue;
    }

    const UIEventMap::HandlerCollection& UIEventMap::GetEventHandlers() const
    {
        return eventHandlers;
    }

    const UIEventMap::HandlerCollection& UIEventMap::GetDelayedEventHandlers() const
    {
        return delayedEventHandlers;
    }

    const UIEventMap::HandlerDictionary& UIEventMap::GetAppEventHandlers() const
    {
        return appEventHandlers;
    }

    const UIEventMap::HandlerDictionary& UIEventMap::GetDelayedAppEventHandlers() const
    {
        return delayedAppEventHandlers;
    }
}