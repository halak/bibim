#include <Bibim/ScriptStack.h>
#include <Bibim/Assert.h>

namespace Bibim
{
    static const uint DefaultStackSize = 1024;

    ScriptStack::ScriptStack()
        : items(DefaultStackSize),
          topIndex(-1)
    {
    }

    ScriptStack::ScriptStack(int capacity)
        : items(capacity),
          topIndex(-1)
    {
        BBAssertDebug(static_cast<int>(items.size()) == capacity);
    }

    ScriptStack::~ScriptStack()
    {
    }

    void ScriptStack::Push(const Item& item)
    {
        BBAssert(topIndex < static_cast<int>(items.size() - 1));

        items[topIndex] = item;
        topIndex++;
    }

    void ScriptStack::Pop(int count)
    {
        BBAssert(topIndex + 1 >= count);

        topIndex -= count;

        BBAssertDebug(topIndex >= -1);
    }

    const ScriptStack::Item& ScriptStack::Peek() const
    {
        if (topIndex >= 0)
            return items[topIndex];
        else
            return Item::Empty;
    }

    const ScriptStack::Item& ScriptStack::GetAt(int index) const
    {
        if (index < 0)
            index = topIndex + 1 + index;

        BBAssertDebug(0 <= index && index <= topIndex);
        return items[index];
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const ScriptStack::Item ScriptStack::Item::Empty;

    ScriptStack::Item::Item()
    {
    }

    ScriptStack::Item::Item(const Any& value)
        : Value(value)
    {
    }

    ScriptStack::Item::Item(const Item& original)
        : Value(original.Value)
    {
    }

    ScriptStack::Item& ScriptStack::Item::operator = (const Item& right)
    {
        Value = right.Value;
        return *this;
    }

    bool ScriptStack::Item::operator == (const Item& right) const
    {
        return Value == right.Value;
    }
}