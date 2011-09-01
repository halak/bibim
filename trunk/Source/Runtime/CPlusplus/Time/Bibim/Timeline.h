#pragma once
#ifndef __BIBIM_TIMELINE_H__
#define __BIBIM_TIMELINE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameComponent.h>
#   include <Bibim/IUpdateable.h>
#   include <vector>

    namespace Bibim
    {
        class Timeline : public GameComponent, public IUpdateable
        {
            BBClassFOURCC('T', 'M', 'L', 'N');
            public:
                struct Item
                {
                    IUpdateable*   RawPointer;
                    IUpdateablePtr SharedPointer;

                    inline Item();
                    inline Item(IUpdateable* item);
                    inline Item(IUpdateablePtr item);

                    inline bool operator == (const Item& right) const;
                    inline bool operator != (const Item& right) const;
                };

            public:
                typedef std::vector<Item> ItemCollection;
                typedef std::vector<IUpdateable*> UpdateableCollection;

            public:
                Timeline();
                explicit Timeline(uint32 id);
                virtual ~Timeline();

                virtual void Update(float dt, uint timestamp);

                void Add(IUpdateable* item);
                void Add(IUpdateablePtr item);
                bool Remove(IUpdateable* item);
                bool Remove(IUpdateablePtr item);
                void RemoveAt(int index);
                void Clear();

                const ItemCollection& GetItems() const;

                float GetSpeed() const;
                void  SetSpeed(float value);

                virtual IUpdateable* QueryUpdateableInterface();

            private:
                ItemCollection items;
                UpdateableCollection temporaryItems;
                float speed;
                uint lastTimestamp;
        };
    }

#   include <Bibim/Timeline.inl>

#endif