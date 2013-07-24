#pragma once
#ifndef __BIBIM_TIMELINE_H__
#define __BIBIM_TIMELINE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UpdateableGameModule.h>
#   include <vector>

    namespace Bibim
    {
        class Timeline : public UpdateableGameModule
        {
            BBModuleClass(Timeline, UpdateableGameModule, 'T', 'M', 'L', 'N');
            public:
                typedef std::vector<IUpdateable*> ItemCollection;
                typedef std::vector<SharedObjectPtr> ObjectCollection;

            public:
                Timeline();
                virtual ~Timeline();

                virtual void Update(float dt, int timestamp);

                void Add(IUpdateable* item);
                void Add(IUpdateable* item, SharedObject* object);
                bool Remove(IUpdateable* item);
                void RemoveAt(int index);
                void Clear();
                bool Contains(IUpdateable* item) const;

                inline const ItemCollection& GetItems() const;

                inline float GetSpeed() const;
                void         SetSpeed(float value);

            private:
                ItemCollection items;
                ItemCollection temporaryItems;
                ObjectCollection objects;
                ObjectCollection temporaryObjects;
                float speed;

        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        const Timeline::ItemCollection& Timeline::GetItems() const
        {
            return items;
        }

        float Timeline::GetSpeed() const
        {
            return speed;
        }
    }

#endif