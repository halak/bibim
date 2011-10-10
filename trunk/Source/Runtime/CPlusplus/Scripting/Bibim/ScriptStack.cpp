#include <Bibim/ScriptStack.h>
#include <Bibim/Assert.h>

namespace Bibim
{
    static const uint DefaultBufferSize = 1024 * 64; // 64kb
    static const uint DefaultOffsetStackSize = 256;

    ScriptStack::ScriptStack()
    {
        buffer.reserve(DefaultBufferSize);
        offsetStack.reserve(DefaultOffsetStackSize);
    }

    ScriptStack::ScriptStack(int capacity)
    {
        buffer.reserve(capacity);
        offsetStack.reserve(DefaultOffsetStackSize);
    }

    ScriptStack::~ScriptStack()
    {
    }

    byte* ScriptStack::Push(int size)
    {
        const int offset = static_cast<int>(buffer.size());
        offsetStack.push_back(offset);
        buffer.resize(buffer.size() + size);

        if (size > 0)
            return &buffer[offset];
        else
            return nullptr;
    }

    void ScriptStack::Pop(int count)
    {
        if (count == 0)
            return;

        BBAssertDebug(count <= static_cast<int>(offsetStack.size()));

        for (; count > 1; count--)
            offsetStack.pop_back();

        buffer.resize(offsetStack.back());
        offsetStack.pop_back();
    }

    byte* ScriptStack::Peek(int& outSize)
    {
        BBAssertDebug(IsEmpty() == false);

        const int offset = offsetStack.back();
        BBAssertDebug(0 <= offset && offset < static_cast<int>(buffer.size()));

        outSize = static_cast<int>(buffer.size()) - offset;
        return &buffer[offset];
    }

    const byte* ScriptStack::Peek(int& outSize) const
    {
        BBAssertDebug(IsEmpty() == false);

        const int offset = offsetStack.back();
        BBAssertDebug(0 <= offset && offset < static_cast<int>(buffer.size()));

        outSize = static_cast<int>(buffer.size()) - offset;
        return &buffer[offset];
    }

    byte* ScriptStack::GetAt(int index)
    {
        if (index < 0)
            index = GetTopIndex() + 1 + index;
        BBAssertDebug(0 <= index && index < static_cast<int>(offsetStack.size()));

        const int offset = offsetStack[index];
        BBAssertDebug(0 <= offset && offset < static_cast<int>(buffer.size()));

        return &buffer[offset];
    }

    const byte* ScriptStack::GetAt(int index) const
    {
        if (index < 0)
            index = GetTopIndex() + 1 + index;
        BBAssertDebug(0 <= index && index < static_cast<int>(offsetStack.size()));

        const int offset = offsetStack[index];
        BBAssertDebug(0 <= offset && offset < static_cast<int>(buffer.size()));

        return &buffer[offset];
    }
}