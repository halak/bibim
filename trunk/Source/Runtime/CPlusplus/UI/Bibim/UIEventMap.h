#pragma once
#ifndef __BIBIM_UIEVENTMAP_H__
#define __BIBIM_UIEVENTMAP_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIElement.h>
#   include <Bibim/UIEventID.h>
#   include <map>
#   include <vector>

    namespace Bibim
    {
        class UIEventMap : public UIElement
        {
            BBCreatableObjectClass(UIEventMap, UIElement, UIElement, 'U', 'E', 'V', 'M');
            public:
                typedef std::vector<UIEventHandlerPtr> HandlerCollection;
                typedef std::map<UIEventID, UIEventHandlerPtr> HandlerDictionary;

            public:
                UIEventMap();
                virtual ~UIEventMap();

                bool RaiseEvent(const UIEventID& id, const UIEventArgs& args);

                void AddHandler(const UIEventID& id, UIEventHandler* item);
                void AddDelayedHandler(const UIEventID& id, UIEventHandler* item);
                bool RemoveHandler(const UIEventID& id, UIEventHandler* item);
                bool RemoveDelayedHandler(const UIEventID& id, UIEventHandler* item);
                bool RemoveAllHandlers(const UIEventID& id);
                bool RemoveAllDelayedHandlers(const UIEventID& id);
                void ClearHandlers();
                void ClearDelayedHandlers();

                inline UIAppEventDispatcher* GetEventDispatcher() const;
                void SetEventDispatcher(UIAppEventDispatcher* value);
                inline UIAsyncEventQueue* GetAsyncEventQueue() const;
                void SetAsyncEventQueue(UIAsyncEventQueue* value);

                inline const HandlerCollection& GetEventHandlers() const;
                inline const HandlerCollection& GetDelayedEventHandlers() const;
                inline const HandlerDictionary& GetAppEventHandlers() const;
                inline const HandlerDictionary& GetDelayedAppEventHandlers() const;

            private:
                void Add(HandlerCollection& eventHandlers, HandlerDictionary& appEventHandlers, const UIEventID& id, UIEventHandler* item);
                bool Remove(HandlerCollection& eventHandlers, HandlerDictionary& appEventHandlers, const UIEventID& id, UIEventHandler* item);
                bool RemoveAll(HandlerCollection& eventHandlers, HandlerDictionary& appEventHandlers, const UIEventID& id);

            private:
                UIAppEventDispatcher* eventDispatcher;
                UIAsyncEventQueue* asyncEventQueue;
                HandlerCollection eventHandlers;
                HandlerCollection delayedEventHandlers;
                HandlerDictionary appEventHandlers;
                HandlerDictionary delayedAppEventHandlers;
        };
    }

#   include <Bibim/UIEventMap.inl>

#endif