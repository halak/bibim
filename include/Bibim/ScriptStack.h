#pragma once
#ifndef __BIBIM_SCRIPTSTACK_H__
#define __BIBIM_SCRIPTSTACK_H__

#include <Bibim/FWD.h>
#include <vector>

namespace Bibim
{
    class ScriptStack
    {
        BBThisIsNoncopyableClass(ScriptStack);
        private:
            typedef std::vector<byte> ByteVector;
            typedef std::vector<int>  IntVector;

        public:
            ScriptStack();
            explicit ScriptStack(int capacity);
            ~ScriptStack();

            byte* Push(int size);
            void Pop(int count);

            byte* Peek(int& outSize);
            const byte* Peek(int& outSize) const;
            inline byte* Peek();
            inline const byte* Peek() const;

            byte* GetAt(int index);
            const byte* GetAt(int index) const;

            inline int GetTopIndex() const;
            inline int GetCapacity() const;
            inline bool IsEmpty() const;

        private:
            ByteVector buffer;
            IntVector  offsetStack;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    byte* ScriptStack::Peek()
    {
        int t = 0;
        return Peek(t);
    }

    const byte* ScriptStack::Peek() const
    {
        int t = 0;
        return Peek(t);
    }

    int ScriptStack::GetTopIndex() const
    {
        return static_cast<int>(offsetStack.size()) - 1;
    }

    int ScriptStack::GetCapacity() const
    {
        return static_cast<int>(buffer.capacity());
    }

    bool ScriptStack::IsEmpty() const
    {
        return offsetStack.empty();
    }
}

#endif