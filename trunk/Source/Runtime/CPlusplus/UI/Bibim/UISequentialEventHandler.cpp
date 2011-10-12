#include <Bibim/UISequentialEventHandler.h>
#include <algorithm>

namespace Bibim
{
    UISequentialEventHandler::UISequentialEventHandler()
    {
    }

    UISequentialEventHandler::UISequentialEventHandler(UIEventHandler* first, UIEventHandler* second)
    {
        handlers.resize(2);
        handlers[0] = first;
        handlers[1] = second;
    }

    UISequentialEventHandler::UISequentialEventHandler(int initialCapacity)
    {
        handlers.reserve(initialCapacity);
    }

    UISequentialEventHandler::~UISequentialEventHandler()
    {
    }

    bool UISequentialEventHandler::Invoke(const UIEventArgs& args)
    {
        bool result = false;
        for (HandlerCollection::const_iterator it = handlers.begin(); it != handlers.end(); it++)
        {
            if ((*it)->Invoke(args))
                result = true;
        }

        return result;
    }

    void UISequentialEventHandler::Add(UIEventHandler* item)
    {
        if (item)
            Insert(static_cast<int>(handlers.size()), item);
    }

    void UISequentialEventHandler::Insert(int index, UIEventHandler* item)
    {
        if (item == nullptr)
            return;

        const int numberOfHandlers = static_cast<int>(handlers.size());

        if (index < 0)
            index = 0;
        if (index > numberOfHandlers)
            index = numberOfHandlers;

        if (index == numberOfHandlers)
            handlers.push_back(item);
        else
            handlers.insert(handlers.begin() + index, item);
    }

    bool UISequentialEventHandler::Remove(UIEventHandler* item)
    {
        if (item == nullptr)
            return false;

        UIEventHandlerPtr sharedItem = item;
        HandlerCollection::iterator it = std::find(handlers.begin(), handlers.end(), item);
        if (it != handlers.end())
        {
            handlers.erase(it);
            return true;
        }
        else
            return false;
    }

    void UISequentialEventHandler::RemoveAt(int index)
    {
        BBAssertDebug(0 <= index && index < static_cast<int>(handlers.size()));
        handlers.erase(handlers.begin() + index);
    }

    void UISequentialEventHandler::Clear()
    {
        handlers.clear();
    }

    void UISequentialEventHandler::SetHandlers(const HandlerCollection& value)
    {
        handlers.clear();
        handlers.reserve(value.size());
        for (HandlerCollection::const_iterator it = value.begin(); it != value.end(); it++)
        {
            if (*it)
                handlers.push_back(*it);
        }
    }

    void UISequentialEventHandler::MoveHandlers(HandlerCollection& value)
    {
        BBAssertDebug(std::find(value.begin(), value.end(), nullptr) == value.end());

        handlers.clear();
        handlers.swap(value);
    }

    bool UISequentialEventHandler::IsSequence() const
    {
        return true;
    }

    UIElement* UISequentialEventHandler::Create(StreamReader& /*reader*/, UIElement* /*existingInstance*/)
    {
        return nullptr;
    }
}