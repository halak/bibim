#pragma once
#ifndef __BIBIM_SCRIPTSTACK_H__
#define __BIBIM_SCRIPTSTACK_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Any.h>
#   include <vector>

    namespace Bibim
    {
        class ScriptStack
        {
            BBThisIsNoncopyableClass(ScriptStack);
            public:
                struct Item
                {
                    Any Value;

                    Item();
                    Item(const Any& value);
                    Item(const Item& original);

                    Item& operator = (const Item& right);
                    bool operator == (const Item& right) const;
                    inline bool operator != (const Item& right) const;

                    static const Item Empty;
                };

                typedef std::vector<Item> Items;

            public:
                ScriptStack();
                ScriptStack(int capacity);
                ~ScriptStack();

                void Push(const Item& item);
                void Pop(int count);
                const Item& Peek() const;
                const Item& GetAt(int index) const;

                inline const Items& GetItems() const;
                inline int GetTopIndex() const;
                inline int GetCapacity() const;

            private:
                Items items;
                int topIndex;
        };
    }

#   include <Bibim/ScriptStack.inl>

#endif