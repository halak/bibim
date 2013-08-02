#pragma once
#ifndef __BIBIM_UIAPPEVENTDISPATCHER_H__
#define __BIBIM_UIAPPEVENTDISPATCHER_H__

#include <Bibim/FWD.h>
#include <Bibim/UIEventDispatcher.h>
#include <Bibim/UIEventID.h>
#include <map>

namespace Bibim
{
    class UIAppEventDispatcher : public UIEventDispatcher
    {
        BBModuleClass(UIAppEventDispatcher, UIEventDispatcher, 'U', 'I', 'A', 'P');
        public:
            typedef std::multimap<UIEventID, UIEventMap*> SubscriptionMap;

        public:
            UIAppEventDispatcher();
            virtual ~UIAppEventDispatcher();

            void RaiseEvent(const UIEventID& id, const UIEventArgs& args) const;

        private:
            friend class UIEventMap;
            void Subscribe(UIEventMap* subscriber, const UIEventID& id);
            void Unsubscribe(UIEventMap* subscriber, const UIEventID& id);
            void UnsubscribeAll(UIEventMap* subscriber);

        private:
            SubscriptionMap subscriptionTable;
    };
}

#endif