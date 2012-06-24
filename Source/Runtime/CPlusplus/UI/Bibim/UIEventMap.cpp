#include <Bibim/UIEventMap.h>
#include <Bibim/UIAppEventDispatcher.h>
#include <Bibim/UIAsyncEventQueue.h>
#include <Bibim/UIEventHandler.h>
#include <Bibim/UISequentialEventHandler.h>

namespace Bibim
{
    BBImplementsComponent(UIEventMap);

    UIEventMap::UIEventMap()
        : eventDispatcher(nullptr),
          asyncEventQueue(nullptr)
    {
    }

    UIEventMap::~UIEventMap()
    {
        eventHandlers.clear();
        delayedEventHandlers.clear();
        appEventHandlers.clear();
        delayedAppEventHandlers.clear();

        if (eventDispatcher)
            eventDispatcher->UnsubscribeAll(this);
    }

    bool UIEventMap::RaiseEvent(const UIEventID& id, const UIEventArgs& args)
    {
        bool result = false;
        
        if (id.GetType() != UIEventID::ApplicationType)
        {
            const int index = static_cast<int>(id.GetType());

            if (index < static_cast<int>(eventHandlers.size()))
            {
                UIEventHandlerPtr handler = eventHandlers[index];
                if (handler)
                    result = handler->Invoke(args);
            }

            if (asyncEventQueue)
            {
                if (index < static_cast<int>(delayedEventHandlers.size()))
                {
                    if (delayedEventHandlers[index])
                        asyncEventQueue->Enqueue(delayedEventHandlers[index], args);
                }
            }
        }
        else
        {
            HandlerDictionary::const_iterator it = appEventHandlers.find(id);
            if (it != appEventHandlers.end())
                result = (*it).second->Invoke(args);

            if (asyncEventQueue)
            {
                HandlerDictionary::const_iterator itDelayed = appEventHandlers.find(id);
                if (itDelayed != appEventHandlers.end())
                    asyncEventQueue->Enqueue((*itDelayed).second, args);
            }
        }

        return result;
    }

    void UIEventMap::AddHandler(const UIEventID& id, UIEventHandler* item)
    {
        Add(eventHandlers, appEventHandlers, id, item);
    }

    void UIEventMap::AddDelayedHandler(const UIEventID& id, UIEventHandler* item)
    {
        Add(delayedEventHandlers, delayedAppEventHandlers, id, item);
    }

    void UIEventMap::Add(HandlerCollection& eventHandlers, HandlerDictionary& appEventHandlers, const UIEventID& id, UIEventHandler* item)
    {
        if (item == nullptr)
            return;

        if (id.GetType() != UIEventID::ApplicationType)
        {
            const int index = static_cast<int>(id.GetType());

            if (index >= static_cast<int>(eventHandlers.size()))
                eventHandlers.resize(index + 1);

            if (UIEventHandler* existingHandler = eventHandlers[index])
            {
                if (existingHandler->IsSequence())
                    static_cast<UISequentialEventHandler*>(existingHandler)->Add(item);
                else
                    eventHandlers[index] = new UISequentialEventHandler(existingHandler, item);
            }
            else
                eventHandlers[index] = item;
        }
        else
        {
            HandlerDictionary::iterator it = appEventHandlers.find(id);
            if (it != appEventHandlers.end())
            {
                UIEventHandler* existingHandler = (*it).second;
                if (existingHandler->IsSequence())
                    static_cast<UISequentialEventHandler*>(existingHandler)->Add(item);
                else
                    (*it).second = new UISequentialEventHandler(existingHandler, item);
            }
            else
            {
                appEventHandlers.insert(HandlerDictionary::value_type(id, item));
                if (eventDispatcher)
                    eventDispatcher->Subscribe(this, id);
            }
        }
    }

    bool UIEventMap::RemoveHandler(const UIEventID& id, UIEventHandler* item)
    {
        return Remove(eventHandlers, appEventHandlers, id, item);
    }

    bool UIEventMap::RemoveDelayedHandler(const UIEventID& id, UIEventHandler* item)
    {
        return Remove(delayedEventHandlers, delayedAppEventHandlers, id, item);
    }
    
    bool UIEventMap::Remove(HandlerCollection& eventHandlers, HandlerDictionary& appEventHandlers, const UIEventID& id, UIEventHandler* item)
    {
        if (item == nullptr)
            return false;

        if (id.GetType() != UIEventID::ApplicationType)
        {
            const int index = static_cast<int>(id.GetType());

            UIEventHandler* existingHandler = eventHandlers[index];
            if (existingHandler == nullptr)
                return false;

            if (existingHandler == item)
            {
                eventHandlers[index] = nullptr;
                return true;
            }

            if (existingHandler->IsSequence())
            {
                if (static_cast<UISequentialEventHandler*>(existingHandler)->Remove(item))
                {
                    if (static_cast<UISequentialEventHandler*>(existingHandler)->GetHandlers().empty())
                        eventHandlers[index] = nullptr;

                    return true;
                }
            }
        }
        else
        {
            HandlerDictionary::iterator it = appEventHandlers.find(id);
            if (it == appEventHandlers.end())
                return false;

            UIEventHandler* existingHandler = (*it).second;
            if (existingHandler == item)
            {
                if (eventDispatcher)
                    eventDispatcher->Unsubscribe(this, id);

                appEventHandlers.erase(it);
                return true;
            }

            if (existingHandler->IsSequence())
            {
                if (static_cast<UISequentialEventHandler*>(existingHandler)->Remove(item))
                {
                    if (static_cast<UISequentialEventHandler*>(existingHandler)->GetHandlers().empty())
                    {
                        if (eventDispatcher)
                            eventDispatcher->Unsubscribe(this, id);

                        appEventHandlers.erase(it);
                    }

                    return true;
                }
            }
        }

        return false;
    }

    bool UIEventMap::RemoveAllHandlers(const UIEventID& id)
    {
        return RemoveAll(eventHandlers, appEventHandlers, id);
    }

    bool UIEventMap::RemoveAllDelayedHandlers(const UIEventID& id)
    {
        return RemoveAll(delayedEventHandlers, delayedAppEventHandlers, id);
    }
    
    bool UIEventMap::RemoveAll(HandlerCollection& eventHandlers, HandlerDictionary& appEventHandlers, const UIEventID& id)
    {
        if (id.GetType() != UIEventID::ApplicationType)
        {
            const int index = static_cast<int>(id.GetType());

            if (index < static_cast<int>(eventHandlers.size()) && eventHandlers[index] != nullptr)
            {
                eventHandlers[index] = nullptr;
                return true;
            }
            else
                return false;
        }
        else
        {
            HandlerDictionary::iterator it = appEventHandlers.find(id);
            if (it != appEventHandlers.end())
            {
                appEventHandlers.erase(it);
                return true;
            }
            else
                return false;
        }
    }

    void UIEventMap::ClearHandlers()
    {
        eventHandlers.clear();
        appEventHandlers.clear();
    }

    void UIEventMap::ClearDelayedHandlers()
    {
        delayedEventHandlers.clear();
        delayedAppEventHandlers.clear();
    }

    void UIEventMap::SetEventDispatcher(UIAppEventDispatcher* value)
    {
        if (eventDispatcher != value)
        {
            if (eventDispatcher)
                eventDispatcher->UnsubscribeAll(this);

            eventDispatcher = value;

            if (eventDispatcher)
            {
                for( HandlerDictionary::const_iterator it = appEventHandlers.begin(); it != appEventHandlers.end(); ++it )
                    eventDispatcher->Subscribe(this, (*it).first);
                for( HandlerDictionary::const_iterator it = delayedAppEventHandlers.begin(); it != delayedAppEventHandlers.end(); ++it )
                {
                    if (appEventHandlers.find((*it).first) == appEventHandlers.end())
                        eventDispatcher->Subscribe(this, (*it).first);
                }
            }
        }
    }

    void UIEventMap::SetAsyncEventQueue(UIAsyncEventQueue* value)
    {
        asyncEventQueue = value;
    }

    void UIEventMap::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        BBBreak();
    }

    void UIEventMap::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        BBBreak();
    }
}