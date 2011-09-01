#include <Bibim/PCH.h>
#include <Bibim/UIAppEventDispatcher.h>
#include <Bibim/UIEventMap.h>

namespace Bibim
{
    UIAppEventDispatcher::UIAppEventDispatcher()
    {
    }

    UIAppEventDispatcher::~UIAppEventDispatcher()
    {
    }

    void UIAppEventDispatcher::RaiseEvent(const UIEventID& id, const UIEventArgs& args) const
    {
        BBAssert(id.GetType() == UIEventID::ApplicationType);

        SubscriptionMap::const_iterator itBegin = subscriptionTable.lower_bound(id);
        SubscriptionMap::const_iterator itEnd = subscriptionTable.upper_bound(id);
        for (SubscriptionMap::const_iterator it = itBegin; it != itEnd; it++)
            (*it).second->RaiseEvent(id, args);
    }
    
    void UIAppEventDispatcher::Subscribe(UIEventMap* subscriber, const UIEventID& id)
    {
        // �� �Լ��� ȣ���ϴ� UIEventMap���� �ߺ��� UIEventID�� ������ ��û���� �ʴ´�.
        // ������ Bug�� ���� �� ������ Debug Build������ Ȯ���� �غ���.

        SubscriptionMap::iterator itBegin = subscriptionTable.lower_bound(id);

#       if (defined(BIBIM_DEBUG))
            if (itBegin != subscriptionTable.end())
            {
                SubscriptionMap::iterator itEnd = subscriptionTable.upper_bound(id);
                for (SubscriptionMap::const_iterator it = itBegin; it != itEnd; it++)
                {
                    BBAssertDebug((*it).second == subscriber);
                }
            }
#       endif

        subscriptionTable.insert(itBegin, SubscriptionMap::value_type(id, subscriber));
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
}