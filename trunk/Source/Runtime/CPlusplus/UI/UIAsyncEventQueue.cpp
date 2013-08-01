#include <Bibim/Config.h>
#include <Bibim/UIAsyncEventQueue.h>
#include <Bibim/UIEventArgs.h>
#include <Bibim/UIEventHandler.h>

namespace Bibim
{
    UIAsyncEventQueue::UIAsyncEventQueue()
    {
    }

    UIAsyncEventQueue::~UIAsyncEventQueue()
    {
    }

    void UIAsyncEventQueue::Update(float /*dt*/, int /*timestamp*/)
    {
        NotifyAll();
    }

    void UIAsyncEventQueue::NotifyAll()
    {
        ItemCollection temporaryItems;
        temporaryItems.swap(items);

        for (ItemCollection::const_iterator it = temporaryItems.begin(); it != temporaryItems.end(); it++)
            (*it).first->Invoke(*(*it).second);
    }
   
    void UIAsyncEventQueue::Enqueue(UIEventHandler* item, const UIEventArgs& args)
    {
        items.push_back(EventHandlerArgsPair(item, args.Clone()));
    }
}