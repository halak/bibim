#pragma once
#ifndef __BIBIM_UIASYNCEVENTQUEUE_H__
#define __BIBIM_UIASYNCEVENTQUEUE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UpdateableGameComponent.h>
#   include <vector>

    namespace Bibim
    {
        class UIAsyncEventQueue : public UpdateableGameComponent
        {
            BBClassFOURCC('U', 'A', 'E', 'Q');
            public:
                typedef std::pair<UIEventHandlerPtr, UIEventArgsPtr> EventHandlerArgsPair;
                typedef std::vector<EventHandlerArgsPair> ItemCollection;

            public:
                UIAsyncEventQueue();
                virtual ~UIAsyncEventQueue();

                virtual void Update(float dt, uint timestamp);

                void NotifyAll();
   
                void Enqueue(UIEventHandler* item, const UIEventArgs& args);

            private:
                Timeline* timeline;
                ItemCollection items;
        };
    }

#   include <Bibim/UIAsyncEventQueue.inl>

#endif