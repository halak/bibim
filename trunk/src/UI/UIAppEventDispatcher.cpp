#include <Bibim/Config.h>
#include <Bibim/UIAppEventDispatcher.h>
#include <Bibim/UIEventMap.h>

namespace Bibim
{
    UIAppEventDispatcher::UIAppEventDispatcher()
    {
    }

    UIAppEventDispatcher::~UIAppEventDispatcher()
    {
        SubscriptionMap table;
        table.swap(subscriptionTable);

        UIEventMapSet set;
        set.swap(instances);

        for (UIEventMapSet::const_iterator it = set.begin(); it != set.end(); it++)
        {
            BBAssert((*it)->GetEventDispatcher() == this);
            (*it)->SetEventDispatcher(nullptr);
        }
    }

    void UIAppEventDispatcher::RaiseEvent(const UIEventID& id, const UIEventArgs& args) const
    {
        BBAssert(id.GetType() == UIEventID::ApplicationType);

        SubscriptionMap::const_iterator begin = subscriptionTable.lower_bound(id);
        SubscriptionMap::const_iterator end = subscriptionTable.upper_bound(id);
        for (SubscriptionMap::const_iterator it = begin; it != end; it++)
            (*it).second->RaiseEvent(id, args);
    }
    
    void UIAppEventDispatcher::Subscribe(UIEventMap* subscriber, const UIEventID& id)
    {
        // 이 함수를 호출하는 UIEventMap에서 중복된 UIEventID는 구독을 요청하지 않습니다.
        // 하지만 Bug가 있을 수 있으니 Debug Build에서는 확인을 해봅니다.

        SubscriptionMap::iterator begin = subscriptionTable.lower_bound(id);

#       if (defined(BIBIM_DEBUG))
            if (begin != subscriptionTable.end())
            {
                SubscriptionMap::iterator end = subscriptionTable.upper_bound(id);
                for (SubscriptionMap::const_iterator it = begin; it != end; it++)
                {
                    BBAssertDebug((*it).second != subscriber);
                }
            }
#       endif

        subscriptionTable.insert(begin, SubscriptionMap::value_type(id, subscriber));
    }

    void UIAppEventDispatcher::Unsubscribe(UIEventMap* subscriber, const UIEventID& id)
    {
        SubscriptionMap::iterator it = subscriptionTable.lower_bound(id);
        BBAssertDebug(it != subscriptionTable.end());

        SubscriptionMap::iterator itEnd = subscriptionTable.upper_bound(id);
        for(; it != itEnd; it++)
        {
            if ((*it).second == subscriber)
            {
                subscriptionTable.erase(it);
                break;
            }
        }
    }

    void UIAppEventDispatcher::UnsubscribeAll(UIEventMap* subscriber)
    {
        for (SubscriptionMap::iterator it = subscriptionTable.begin(); it != subscriptionTable.end();)
        {
            if ((*it).second == subscriber)
                subscriptionTable.erase(it++);
            else
                it++;
        }
    }

    void UIAppEventDispatcher::Register(UIEventMap* o)
    {
        BBAssertDebug(instances.find(o) == instances.end());
        instances.insert(o);
    }

    void UIAppEventDispatcher::Unregister(UIEventMap* o)
    {
        instances.erase(o);
    }
}